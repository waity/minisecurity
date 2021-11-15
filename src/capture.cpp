#include "capture.h"
#include <thread>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Capture::Capture(std::string _name)
{
    name = _name;
    cap = new VideoCapture(name);
    worker = std::thread{&Capture::work, this};
}

Mat Capture::getFrame()
{
    Mat mat;
    cap->retrieve(mat);
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
        cap->grab();
    }
}