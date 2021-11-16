#include "capture.h"
#include <thread>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

/* 
Wraps cv::VideoCapture with a thread consuming the stream. Get returns the
most recent frame.
*/
Capture::Capture(std::string _name)
{
    newFrame = false;
    name = _name;
    cap = new VideoCapture(name);
    worker = std::thread{&Capture::work, this};
}

Mat Capture::getFrame()
{
    Mat mat;
    if ( !newFrame ) {
        return mat;
    }

    cap->retrieve(mat);
    newFrame = false;
    return mat;
}

bool Capture::isOpened()
{
    return cap->isOpened();
}

void Capture::release()
{
    cap->release();
}

void Capture::work()
{
    while (1) {
        if ( cap->grab() ) {
            newFrame = true;
        }
    }
}