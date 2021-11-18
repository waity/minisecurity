#include "processor.h"
#include "opencv2/opencv.hpp"
#include <thread>
#include <chrono>


Processor::Processor()
{
  worker = std::thread{&Processor::work, this};
}

cv::Mat Processor::gray_and_blur(cv::Mat in) {
  cv::Mat gray, blur;

  cv::Size size = cv::Size(99,99);

  cv::cvtColor(in, gray, cv::COLOR_BGR2GRAY);
  cv::blur(gray, blur, size);

  return blur;
}

cv::Mat Processor::diff_image(cv::Mat in1, cv::Mat in2) {
  cv::Mat gray1, gray2, diff, threshold, eroded, dilated;

  cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3));
  int sensitivity = 4;
  
  gray1 = gray_and_blur(in1);
  gray2 = gray_and_blur(in2);
  cv::absdiff(gray1, gray2, diff);
  cv::threshold(diff, threshold, sensitivity, 255, 3);
  cv::erode(threshold, eroded, element);
  cv::dilate(eroded, dilated, element);
  return dilated;
}

bool Processor::detect_movement(cv::Mat in, int scale) {
  std::vector<std::vector<cv::Point>> contours, filtered;
  std::vector<cv::Vec4i> hierarchy;

  double min_size = 1000 / scale;
  
  cv::findContours(in, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
  for ( int i = 0; i < contours.size(); i++ ) {
    double area = cv::contourArea(contours.at(i));
    if ( area > min_size ) {
      filtered.push_back(contours.at(i));
    }
  }
  return filtered.size() > 0;
}

void Processor::store(cv::Mat frame, cv::Mat previous) {
  lock.lock();
  frames.push_back(Frame(frame, previous));
  lock.unlock();
}

void Processor::work() {
  while ( 1 ) {
    // std::cout << "worker working...\n";
    lock.lock();
    if ( frames.size() > 0 ) {
      std::cout << frames.size() << " frames\n";
      // Frame frame = frames.back();
      frames.pop_back();
    }
    else {
      std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
    lock.unlock();
  }
}

Frame::Frame(cv::Mat _frame, cv::Mat _previous) {
  frame = _frame.clone();
  previous = _previous.clone();
}