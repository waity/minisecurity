#include "capture.h"
#include <thread>
#include "opencv2/opencv.hpp"
#include <chrono>
#include <thread>

using namespace std;
using namespace cv;

/* 
Wraps cv::VideoCapture with a thread consuming the stream. Get returns the
most recent frame.
*/
Capture::Capture(std::string _name)
{
    std::atomic<bool> newFrame(false);
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

    lock.lock();
    cap->retrieve(mat);
    if ( mat.empty() ) {
        cap->release();
        delete cap;
        cap = new VideoCapture(name);
    }
    lock.unlock();
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
        lock.lock();
        if ( cap->grab() ) {
            newFrame = true;
        }
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
}