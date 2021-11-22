#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"
#include <mutex>
#include <thread>
#include "classifier.h"

class Frame {
  private:
    cv::Mat frame;
    cv::Mat previous;
  public:
    Frame(cv::Mat _frame, cv::Mat _previous);
    cv::Mat getFrame();
    cv::Mat getPrevious();
};

class Processor {
  private:
    std::thread worker;
    std::mutex lock;
    std::vector<Frame> to_process;
    cv::Mat last_processed;
    cv::Mat gray_and_blur(cv::Mat in);
    cv::Mat diff_image(cv::Mat in1, cv::Mat in2);
    bool detect_movement(cv::Mat in, int scale);
    void work();
    Classifier classifier;
  public:
    Processor();
    void store(cv::Mat frame, cv::Mat previous);
    cv::Mat retrieve();
};

#endif