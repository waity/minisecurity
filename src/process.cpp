#include "process.h"
#include "opencv2/opencv.hpp"

cv::Mat gray_and_blur(cv::Mat in) {
  cv::Mat gray, blur;

  cv::Size size = cv::Size(99,99);

  cv::cvtColor(in, gray, cv::COLOR_BGR2GRAY);
  cv::blur(gray, blur, size);

  return blur;
}

cv::Mat diff_image(cv::Mat in1, cv::Mat in2) {
  cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(9,9));

  cv::Mat gray1, gray2, diff, threshold, eroded, dilated;
  int sensitivity = 10;
  gray1 = gray_and_blur(in1);
  gray2 = gray_and_blur(in2);
  cv::absdiff(gray1, gray2, diff);
  cv::threshold(diff, threshold, sensitivity, 255, 3);
  cv::erode(threshold, eroded, element);
  cv::dilate(eroded, dilated, element);
  return dilated;
}

bool detect_movement(cv::Mat in, int scale) {
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