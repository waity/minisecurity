#include <iostream>
#include <cstring>
#include <time.h>
#include "capture.h"
#include "process.h"
#include "classifier.h"

using namespace std;

bool DEBUG = false;
bool PI = false;

int main(int argc, char* argv[]) {
  Capture capture("rtsp://admin:123456@192.168.1.101:554/h264");
  Classifier classifier;

  if ( !capture.isOpened() ) {
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  cv::Mat previous;
	
  while (1) {
    cv::Mat frame, diff;
    frame = capture.getFrame();
    if ( frame.empty() ) {
      continue;
    }

    if ( previous.empty() ) {
      previous = frame.clone();
      continue;
    }

    diff = diff_image(frame, previous);
    bool movement = detect_movement(diff);
    if ( movement && classifier.detect_person(frame) ) {
      std::cout << "person detected\n";
    }
    else {
      std::cout << "no person\n";
    }

    previous = frame.clone();

    if ( PI ) {
      int down_width = 300;
      int down_height = 200;
      Mat resized_down;
      cv::resize(frame, resized_down, Size(down_width, down_height), INTER_LINEAR);
      frame = resized_down;
    }

    if (DEBUG)
      imshow( "Frame", frame );

    char c=(char)waitKey(25);
    if(c==27)
      break;
  }

  capture.release();
  destroyAllWindows();
	
  return 0;
}