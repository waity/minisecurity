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
    const int LEAD = 20;
    std::vector<cv::Mat> frames;
    cv::Mat previous;
    cv::Mat average;
    cv::Mat frame;
    bool detect;
    int last_alarm = -1;
    Processor p;
    void write(ProcessedFrame pf);
    void save(std::vector<cv::Mat> frames);
  public:
    DVR(Capture *_capture, bool _detect);
    cv::Mat tick();
};

#endif