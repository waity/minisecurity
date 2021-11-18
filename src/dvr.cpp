#include "dvr.h"
#include "capture.h"
#include "processor.h"

DVR::DVR(Capture *_c) 
{
  c = _c;
}

cv::Mat DVR::tick() 
{
  int SCALE = 4;
  cv::Mat diff, full_frame, view;
  Processor* p = new Processor();

  full_frame = c->getFrame();
  if ( full_frame.empty() ) {
    return frame;
  }

  cv::resize(full_frame, frame, cv::Size(full_frame.cols / SCALE, full_frame.rows / SCALE), cv::INTER_LINEAR);
  // frame = full_frame;



  if ( previous.empty() ) {
    previous = frame.clone();
    return diff;
  }
  else {
    p->store(frame, previous);
  }

  view = frame;

  // diff = diff_image(frame, previous);
  // bool movement = detect_movement(diff, SCALE);
  // std::cout << movement << "\n";
  // if ( movement ) {
    // view = classifier.get_objects(frame);
  // }
  previous = frame.clone();
  return view;
}
