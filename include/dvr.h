#ifndef DVR_H
#define DVR_H

#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"
#include "capture.h"
#include "classifier.h"
#include <thread>
#include <mutex>

class DVR {
  private:
    Capture* c;
    std::vector<cv::Mat> frames;
    cv::Mat previous;
    cv::Mat frame;
    Classifier classifier;
  public:
    DVR(Capture *_c);
    cv::Mat tick();
};

#endif