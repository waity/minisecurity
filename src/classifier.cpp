#include "classifier.h"
#include <fstream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace dnn;


const cv::Scalar colors[] = {
    {0, 255, 255},
    {255, 255, 0},
    {0, 255, 0},
    {255, 0, 0}
};
const auto NUM_COLORS = sizeof(colors)/sizeof(colors[0]);

Classifier::Classifier() {
  net = cv::dnn::readNetFromDarknet("yolo/yolov3-tiny.cfg", "yolo/yolov3-tiny.weights");
  net.setPreferableBackend(DNN_BACKEND_CUDA);
  net.setPreferableTarget(DNN_TARGET_CUDA);
  std::ifstream ifs(std::string("yolo/coco.names").c_str());
  std::string line;
  while ( std::getline(ifs, line) ) {
    class_names.push_back(line);
  }

  output_names = net.getUnconnectedOutLayersNames();
}

bool Classifier::detect_person(cv::Mat in) 
{
  int num_classes = output_names.size();
  cv::Mat resized;
  std::vector<cv::Mat> detections;
  cv::Mat blob = cv::dnn::blobFromImage(in, 1/255.0, cv::Size(416, 416), cv::Scalar(), true, true);
  net.setInput(blob);
  net.forward(detections, output_names);

  float confidence_threshold = 0.1;

  std::vector<int> indices[num_classes];
  std::vector<float> scores[num_classes];

  for (cv::Mat& output : detections) {
    const int detections = output.rows;
    for (int i = 0; i < detections; i++) {
      for (int c = 0; c < num_classes; c++) {
          int confidence = *output.ptr<float>(i, 5 + c);
          if ( confidence >= confidence_threshold ) { //&& class_names[c] == "person" ) {
            std::cout << "confidence: " << confidence << " thing: " << class_names[c] << "\n" << std::endl;
            return true;
          }
      }
    }
  }

  return false;
}

cv::Mat Classifier::get_objects(cv::Mat in) 
{
  int num_classes = output_names.size();
  cv::Mat resized;
  std::vector<cv::Mat> detections;
  cv::Mat blob = cv::dnn::blobFromImage(in, 1/255.0, cv::Size(416, 416), cv::Scalar(), true, true);
  net.setInput(blob);

  net.forward(detections, output_names);

  std::vector<int> indices[num_classes];
  std::vector<cv::Rect> boxes[num_classes];
  std::vector<float> scores[num_classes];

  for (auto& output : detections) {
    const auto num_boxes = output.rows;
    for (int i = 0; i < num_boxes; i++) {
      auto x = output.at<float>(i, 0) * in.cols;
      auto y = output.at<float>(i, 1) * in.rows;
      auto width = output.at<float>(i, 2) * in.cols;
      auto height = output.at<float>(i, 3) * in.rows;
      cv::Rect rect(x - width/2, y - height/2, width, height);
      for (int c = 0; c < num_classes; c++) {
          auto confidence = *output.ptr<float>(i, 5 + c);
          if (confidence >= 0.1) {
            boxes[c].push_back(rect);
            scores[c].push_back(confidence);
          }
      }
    }
  }
  for (int c = 0; c < num_classes; c++)
    cv::dnn::NMSBoxes(boxes[c], scores[c], 0.0, 0.4, indices[c]);

    for (int c= 0; c < num_classes; c++)
    {
      for (size_t i = 0; i < indices[c].size(); ++i)
      {
        const auto color = colors[c % NUM_COLORS];

        auto idx = indices[c][i];
        const auto& rect = boxes[c][idx];
        cv::rectangle(in, cv::Point(rect.x, rect.y), cv::Point(rect.x + rect.width, rect.y + rect.height), color, 3);

        std::ostringstream label_ss;

        // std::cout << "classifier: " << class_names[c] << ": " << std::fixed << std::setprecision(2) << scores[c][idx] << "\n";
        label_ss << class_names[c] << ": " << std::fixed << std::setprecision(2) << scores[c][idx];
        auto label = label_ss.str();
        
        int baseline;
        auto label_bg_sz = cv::getTextSize(label.c_str(), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, 1, &baseline);
        cv::rectangle(in, cv::Point(rect.x, rect.y - label_bg_sz.height - baseline - 10), cv::Point(rect.x + label_bg_sz.width, rect.y), color, cv::FILLED);
        cv::putText(in, label.c_str(), cv::Point(rect.x, rect.y - baseline - 5), cv::FONT_HERSHEY_COMPLEX_SMALL, 1, cv::Scalar(0, 0, 0));
      }
  }

  return in;
}
