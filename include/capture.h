#ifndef CAPTURE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define CAPTURE_H

#include <mutex>
#include <queue>
#include <thread>
#include "opencv2/opencv.hpp"

using namespace cv;

class Capture {
  private:
    std::mutex mtx;
    std::string name;
    VideoCapture* cap;
    std::thread worker;
  public:
    Capture(std::string);
    Mat getFrame();
    void release();
    bool isOpened();
    void work();
};

#endif