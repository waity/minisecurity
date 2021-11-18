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
    cap->set(CAP_PROP_BUFFERSIZE, 3);
    cap->set(CAP_PROP_FRAME_WIDTH, 320);
    cap->set(CAP_PROP_FRAME_HEIGHT, 180);
    worker = std::thread{&Capture::work, this};
}

Mat Capture::getFrame()
{
    Mat mat, copy;
    if ( !newFrame ) {
        return mat;
    }

    lock.lock();
    cap->retrieve(mat);
    copy = mat.clone();
    if ( mat.empty() ) {
        std::cout << "resetting\n" << std::endl;
        cap->release();
        delete cap;
        cap = new VideoCapture(name);
        cap->set(CAP_PROP_BUFFERSIZE, 3);
        cap->set(CAP_PROP_FRAME_WIDTH, 320);
        cap->set(CAP_PROP_FRAME_HEIGHT, 180);
    }
    lock.unlock();
    return copy;
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