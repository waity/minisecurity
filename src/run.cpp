#include <iostream>
#include <cstring>
#include <time.h>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
  VideoCapture cap("rtsp://admin:123456@192.168.1.101:554/h264"); 
  // VideoCapture cap(0); 
   
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  float start = clock();
	
  while(1){
    float now = clock();
    if ( ((now - start) / CLOCKS_PER_SEC) > 15 ) {
      break;
    }
    Mat frame;
    cap >> frame;
    if (frame.empty())
      break;
    imshow( "Frame", frame );
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  cap.release();
  destroyAllWindows();
	
  return 0;
}