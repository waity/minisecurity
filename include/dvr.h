#ifndef DVR_H
#define DVR_H

#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"
#include "capture.h"
#include <thread>
#include <mutex>
#include "processor.h"

class DVR {
  private:
    Capture* capture;
    std::vector<cv::Mat> frames;
    cv::Mat previous;
    cv::Mat frame;
    Processor p;
  public:
    DVR(Capture *_capture);
    cv::Mat tick();
};

#endif