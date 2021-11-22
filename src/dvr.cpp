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
  cv::Mat full_frame, view, resized_frame;

  frame = capture->getFrame();
  if ( frame.empty() ) {
    return view;
  }

  view = frame;

  cv::resize(frame, resized_frame, cv::Size(frame.cols / SCALE, frame.rows / SCALE), cv::INTER_LINEAR);
  // view = resized_frame;

  if ( previous.empty() ) {
    previous = resized_frame.clone();
    return view;
  }
  else {
    previous = resized_frame.clone();
    p.store(resized_frame, previous);
    cv::Mat temp = p.retrieve();
    if ( !temp.empty() ) {
      view = temp;
    }
  }

  return view;
}
