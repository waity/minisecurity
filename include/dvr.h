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
    int NUM_THREADS = 3;
    float WAIT_TIME = 1 / NUM_THREADS;
    Capture* c;
    std::thread classifier_thread;
    std::mutex classifier_mutex;
    std::vector<std::thread> threads;
    std::vector<cv::Mat> frames;
    std::vector<cv::Mat> classifier_q;
    cv::Mat previous;
    cv::Mat frame;
    Classifier classifier;
  public:
    DVR(Capture *_c);
    cv::Mat tick();
    void classify();
};

#endif