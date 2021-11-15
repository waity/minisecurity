#ifndef TEST_H
#define TEST_H
#include <iostream>
#include <cstring>
#include "opencv2/opencv.hpp"

cv::Mat gray_and_blur(cv::Mat in);
cv::Mat diff_image(cv::Mat in1, cv::Mat in2);
bool detect_movement(cv::Mat in);

#endif