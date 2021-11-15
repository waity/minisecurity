#ifndef CLASSIFIER_H
#define CLASSIFIER_H
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"

class Classifier {
  private:
    cv::dnn::Net net;
    std::vector<std::string> class_names;
    std::vector<std::string> output_names;
  public:
    Classifier();
    cv::Mat get_objects(cv::Mat in);
};

#endif