#include <mutex>
#include <queue>
#include "opencv2/opencv.hpp"

using namespace cv;

class Capture {
  private:
    std::mutex mtx;
    std::string name;
    std::queue<std::string> q;
    VideoCapture* cap;
  public:
    Capture(std::string);
    VideoCapture getCap();
};