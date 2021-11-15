#include "capture.h"
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

Capture::Capture(std::string _name)
{
    name = _name;
    cap = new VideoCapture(name);
}

VideoCapture Capture::getCap()
{
    return *cap;
}