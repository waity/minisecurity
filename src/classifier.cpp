#include "classifier.h"
#include <fstream>
#include "opencv2/opencv.hpp"

Classifier::Classifier() {
  net = cv::dnn::readNetFromDarknet("yolo/yolov3-tiny.cfg", "yolo/yolov3-tiny.weights");

  net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
  net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA);

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

  float confidence_threshold = 0.2;

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
          if ( confidence >= confidence_threshold && class_names[c] == "person" ) {
            return true;
          }
      }
    }
  }

  return false;
}