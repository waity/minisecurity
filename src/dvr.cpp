#include "dvr.h"
#include "capture.h"
#include "process.h"

DVR::DVR(Capture *_c) 
{
  c = _c;
}

cv::Mat DVR::tick() 
{
  cv::Mat diff;
  frame = c->getFrame();
  if ( frame.empty() ) {
    return diff;
  }

  if ( previous.empty() ) {
    previous = frame.clone();
    return diff;
  }

  // diff = diff_image(frame, previous);
  // bool movement = detect_movement(diff);
  // if ( movement && classifier.detect_person(frame) ) {
  //   std::cout << "person detected\n";
  // }
  // else {
  //   std::cout << "no person\n";
  // }

  previous = frame.clone();
  return frame;
}