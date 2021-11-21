#include <iostream>
#include <cstring>
#include <string>
#include "capture.h"
#include "dvr.h"
#include <chrono>
#include <thread>

using namespace std;


int main(int argc, char* argv[]) {
  bool DEBUG = false;
  bool PI = false;
  int FPS = 5;

  for ( int i = 1; i < argc; i++ ) {
    if ( std::strcmp(argv[i], "-debug") == 0 ) {
      DEBUG = true;
    }
    if ( std::strcmp(argv[i], "-pi") == 0 ) {
      PI = true;
    }
  }

  // Capture capture("rtsp://admin:123456@192.168.1.101/554/h264");
  Capture capture("test.mp4");

  // std::vector<cv::Mat> frames;

  DVR dvr(&capture);

  if ( !capture.isOpened() ) {
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while ( 1 ) {
    cv::Mat frame = dvr.tick();
    if ( frame.empty() ) {
      continue;
    }

    // frames.push_back(frame.clone());

    if ( DEBUG && PI ) {
      int pisize_width = 300;
      int pisize_height = 200;
      cv::Mat resized_down;
      cv::resize(frame, resized_down, cv::Size(pisize_width, pisize_height), cv::INTER_LINEAR);
      frame = resized_down;
    }

    if ( DEBUG ) {
      // imshow("Frame", frame);
    }
    char c=(char)cv::waitKey((1.0/FPS)*1000);
    if(c==27)
      break;
  }

  // for WRITING
  // cv::Mat front = frames.front();
  // cv::VideoWriter video("out.mp4", cv::VideoWriter::fourcc('M','P','4','V'), 10, cv::Size(front.cols, front.rows));
  // for ( cv::Mat frame : frames ) {
  //   video.write(frame);
  // }
  // video.release();
  capture.release();
  cv::destroyAllWindows();
	
  return 0;
}