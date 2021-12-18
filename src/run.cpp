#include <iostream>
#include <cstring>
#include <string>
#include "capture.h"
#include "dvr.h"
#include <chrono>
#include <thread>

using namespace std;

const int FPS = 4;
int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;
std::string WINDOW_NAME = "Display";

int main(int argc, char* argv[]) {
  bool DEBUG = false;
  bool PI = false;

  for ( int i = 1; i < argc; i++ ) {
    if ( std::strcmp(argv[i], "-debug") == 0 ) {
      DEBUG = true;
    }
  }

  cv::namedWindow(WINDOW_NAME);
  cv::resizeWindow(WINDOW_NAME, SCREEN_WIDTH, SCREEN_HEIGHT);

  Capture capture("rtsp://admin:123456@192.168.1.104/554/h264");

  DVR dvr(&capture, true);

  if ( !capture.isOpened() ) {
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  // cv::Mat average;

  while ( 1 ) {
    cv::Mat frame = dvr.tick();

    if ( frame.empty() ) {
      continue;
    }

    if ( DEBUG ) {
      cv::imshow(WINDOW_NAME, frame);
    }

    char c=(char)cv::waitKey((1.0/FPS)*1000);
    if(c==27)
      break;
  }
  
  capture.release();
  cv::destroyAllWindows();
	
  return 0;
}