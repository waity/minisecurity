#include <mutex>
#include <queue>

class Capture {
  private:
    std::mutex mtx;
    std::queue<std::string> queue;
    std::string myType;
  public:
    void setType(std::string);
    std::string getType();
};