#include "process.h"
#include "opencv2/opencv.hpp"

cv::Mat gray_and_blur(cv::Mat in) {
  cv::Mat gray, blur;

  cv::Size size = cv::Size(99,99);

  cv::cvtColor(in, gray, cv::COLOR_BGR2GRAY);
  cv::GaussianBlur(gray, blur, size, 25, 0);
  return blur;
}

cv::Mat diff_image(cv::Mat in1, cv::Mat in2) {
  cv::Mat gray1, gray2, diff, threshold, dilate;
  int sensitivity = 10;
  gray1 = gray_and_blur(in1);
  gray2 = gray_and_blur(in2);
  cv::absdiff(gray1, gray2, diff);
  cv::threshold(diff, threshold, sensitivity, 255, 3);
  return threshold;
}