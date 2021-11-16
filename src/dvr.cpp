#include "dvr.h"
#include "capture.h"
#include "process.h"
#include <thread>

DVR::DVR(Capture *_c) 
{
  c = _c;
  classifier_thread = std::thread{&DVR::classify, this};
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

  diff = diff_image(frame, previous);
  bool movement = detect_movement(diff);
  if ( movement ) {
    classifier_q.push_back(frame);
  }
  // if ( movement && classifier.detect_person(frame) ) {
  //   std::cout << "person detected\n";
  // }
  // else {
  //   std::cout << "no person\n";
  // }

  previous = frame.clone();
  return frame;
}

void DVR::classify() {
  while ( 1 ) {
    if ( !classifier_q.empty() ) {
      bool detected = classifier.detect_person(DVR::classifier_q.back());
      DVR::classifier_q.pop_back();
      if ( detected ) {
        std::cout << "person detected\n";
      }
      else {
        std::cout << "no person\n";
      }
    }
  }
}