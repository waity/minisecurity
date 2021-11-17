#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"
#include <thread>

class Classifier {
  private:
    cv::dnn::Net net;
    std::vector<std::string> class_names;
    std::vector<std::string> output_names;
  public:
    Classifier();
    bool detect_person(cv::Mat in);
    cv::Mat get_objects(cv::Mat in);
};

#endif