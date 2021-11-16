#ifndef CAPTURE_H
#define CAPTURE_H

#include <queue>
#include <thread>
#include "opencv2/opencv.hpp"
#include <mutex>

class Capture {
  private:
    std::string name;
    cv::VideoCapture* cap;
    std::thread worker;
    std::mutex lock;
    std::atomic<bool> newFrame;
  public:
    Capture(std::string);
    cv::Mat getFrame();
    void release();
    bool isOpened();
    void work();
};

#endif