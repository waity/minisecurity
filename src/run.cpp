#include <iostream>
#include <cstring>
#include <time.h>
#include "capture.h"
#include "test.h"

using namespace std;
using namespace cv;

bool DEBUG = false;

int main(int argc, char* argv[]) {
  Capture cap("rtsp://admin:123456@192.168.1.101:554/h264"); 
  // VideoCapture cap("rtsp://admin:123456@192.168.1.101:554/h264"); 
   
// Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while(1){

    Mat frame;
    // Capture frame-by-frame
    frame = cap.getFrame();
 
    // If the frame is empty, break immediately
    if (frame.empty())
      continue;

    // Display the resulting frame
    if (DEBUG)
      imshow( "Frame", frame );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}