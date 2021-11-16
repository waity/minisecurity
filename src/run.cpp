#include <iostream>
#include <cstring>
#include <string>
#include "capture.h"
#include "dvr.h"
#include "classifier.h"
#include <chrono>
#include <thread>

using namespace std;


int main(int argc, char* argv[]) {
  bool DEBUG = false;
  bool PI = false;

  for ( int i = 1; i < argc; i++ ) {
    if ( std::strcmp(argv[i], "-debug") == 0 ) {
      DEBUG = true;
    }
    if ( std::strcmp(argv[i], "-pi") == 0 ) {
      PI = true;
    }
  }

  Capture capture("rtsp://admin:123456@192.168.1.101:554/h264");
  DVR dvr(&capture);

  if ( !capture.isOpened() ) {
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while (1) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    cv::Mat frame = dvr.tick();
    if ( frame.empty() ) {
      continue;
    }

    if ( DEBUG && PI ) {
      int down_width = 300;
      int down_height = 200;
      cv::Mat resized_down;
      cv::resize(frame, resized_down, cv::Size(down_width, down_height), cv::INTER_LINEAR);
      frame = resized_down;
    }

    if ( DEBUG ) {
      imshow("Frame", frame);
    }

    char c=(char)cv::waitKey(25);
    if(c==27)
      break;
  }

  capture.release();
  cv::destroyAllWindows();
	
  return 0;
}