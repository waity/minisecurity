#include "dvr.h"
#include "capture.h"
#include "processor.h"

DVR::DVR(Capture *_capture, bool _detect) 
{
  detect = _detect;
  capture = _capture;
}

cv::Mat DVR::tick() 
{
  int SCALE = 4;
  bool RESIZE = true;
  cv::Mat resized_frame;

  frame = capture->getFrame();
  if ( frame.empty() ) {
    return cv::Mat();
  }

  if ( RESIZE ) {
    cv::resize(frame, frame, cv::Size(frame.cols / SCALE, frame.rows / SCALE), cv::INTER_LINEAR);
  }

  if ( !detect ) {
    return frame;
  }

  if ( frame.size() == average.size() ) {
    cv::addWeighted(average, 0.8, frame, 0.2, 0.0, average);
  }
  else {
    average = frame.clone();
  }

  if ( previous.empty() ) {
    previous = frame.clone();
    return frame;
  }
  else {
    p.store(resized_frame, previous, average);
    previous = frame.clone();
    ProcessedFrame pf = p.retrieve();
    if ( !pf.frame.empty() ) {
      frame = pf.frame;
    }
    write(pf);
  }

  return average;
}

void DVR::write(ProcessedFrame pf) 
{
  frames.push_back(pf.frame);

  int length = frames.size();

  std::cout << "LENGTH:" << length << "\t" << "LAST:" << last_alarm << std::endl;
  std::cout << pf.alarm << std::endl;

  if ( !pf.alarm ) {
    if ( last_alarm >= 0 && length - last_alarm >= LEAD) {
      std::vector<cv::Mat> to_save;
      for (cv::Mat frame : frames) {
        to_save.push_back(frame.clone());
      }
      save(to_save);
      frames.clear();
      last_alarm = -1;
    }
    else if ( last_alarm < 0 && length > LEAD ) {
      frames.erase(frames.begin());
    }
  }
  else {
    last_alarm = length;
  }
}

void DVR::save(std::vector<cv::Mat> frames) 
{
  int FPS = 4;
  int codec = cv::VideoWriter::fourcc('M','J','P','G');
  cv::VideoWriter out;

  int width;
  int height;

  bool file_open = false;
  for ( cv::Mat frame : frames ) {
    if ( frame.empty() ) {
      continue;
    }
    else if ( !file_open ) {
      out.open("out.avi", codec, FPS, cv::Size(frame.cols, frame.rows), true);
      file_open = true;
      break;
    }

    out.write(frame);
  }
  out.release();
}