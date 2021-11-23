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
    worker = std::thread{&Capture::work, this};
}

Mat Capture::getFrame()
{
    Mat mat, copy;
    lock.lock();
    if ( !newFrame ) {
        return mat;
    }
    cap->retrieve(mat);
    lock.unlock();
    if ( mat.empty() ) {
        // std::cout << "resetting\n" << std::endl;
        // cap->release();
        // delete cap;
        // cap = new VideoCapture(name);
        // cap->set(CAP_PROP_BUFFERSIZE, 3);
    }
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
        int FPS = 25;
        std::this_thread::sleep_for(std::chrono::milliseconds(int((1.0/FPS)*1000)));
    }
}