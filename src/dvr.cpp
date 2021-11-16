#include "dvr.h"
#include "capture.h"
#include "process.h"

DVR::DVR(Capture *_c) 
{
  c = _c;
}

cv::Mat DVR::tick() 
{
  cv::Mat diff, pre_frame;
  pre_frame = c->getFrame();
  if ( pre_frame.empty() ) {
    return frame;
  }

  cv::resize(pre_frame, frame, cv::Size(pre_frame.cols / 4, pre_frame.rows / 4), cv::INTER_LINEAR);

  if ( previous.empty() ) {
    previous = frame.clone();
    return diff;
  }

  diff = diff_image(frame, previous);
  bool movement = detect_movement(diff, 4);
  if ( movement ) {
    bool detected = classifier.detect_person(frame);
  }
  previous = frame.clone();
  return frame;
}
