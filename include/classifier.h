#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"
#include <thread>

struct ProcessedFrame {
  cv::Mat frame;
  bool alarm;
  ProcessedFrame(cv::Mat _frame, bool _alarm) {
    frame = _frame;
    alarm = _alarm;
  };
  ProcessedFrame(cv::Mat _frame) {
    frame = _frame;
    alarm = false;
  };
    ProcessedFrame() {
    frame = NULL;
    alarm = false;
  };
};

class Classifier {
  private:
    cv::dnn::Net net;
    std::vector<std::string> class_names;
    std::vector<std::string> output_names;
  public:
    Classifier();
    ProcessedFrame get_objects(cv::Mat in);
};

#endif