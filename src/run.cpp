#include <iostream>
#include <cstring>
#include <time.h>
#include "capture.h"
#include "process.h"

using namespace std;
using namespace cv;

bool DEBUG = true;

int main(int argc, char* argv[]) {
  Capture capture("rtsp://admin:123456@192.168.1.101:554/h264");

  if( !capture.isOpened() ){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  Mat previous;
  int i;
	
  while (1) {
    Mat frame, diff;
    frame = capture.getFrame();
    if ( frame.empty() ) {
      continue;
    }

    cout << i << " frame" << std::endl;
    i += 1;

    if ( previous.empty() ) {
      previous = frame.clone();
      continue;
    }

    // frame = gray_and_blur(frame);
    diff = diff_image(frame, previous);

    int down_width = 300;
    int down_height = 200;
    Mat resized_down;
    //resize down
    cv::resize(diff, resized_down, Size(down_width, down_height), INTER_LINEAR);
    if (DEBUG)
      imshow( "Frame", resized_down );

    previous = frame;
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }

  capture.release();
  destroyAllWindows();
	
  return 0;
}