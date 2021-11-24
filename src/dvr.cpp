#include "dvr.h"
#include "capture.h"
#include "processor.h"

DVR::DVR(Capture *_capture) 
{
  capture = _capture;
}

cv::Mat DVR::tick() 
{
  int SCALE = 4;
  bool RESIZE = true;
  cv::Mat full_frame, view, resized_frame;

  frame = capture->getFrame();
  if ( frame.empty() ) {
    return view;
  }

  view = frame;

  if ( RESIZE ) {
    cv::resize(frame, resized_frame, cv::Size(frame.cols / SCALE, frame.rows / SCALE), cv::INTER_LINEAR);
  }

  if ( previous.empty() ) {
    if ( RESIZE ) {
      previous = resized_frame.clone();
    }
    else {
      previous = frame.clone();
    }
    return view;
  }
  else {
    p.store(resized_frame, previous);
    if ( RESIZE ) {
      previous = resized_frame.clone();
    }
    else {
      previous = frame.clone();
    }
    cv::Mat temp = p.retrieve();
    if ( !temp.empty() ) {
      view = temp;
    }
  }

  return view;
}
