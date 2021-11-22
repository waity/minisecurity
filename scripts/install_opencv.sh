# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
# Download and unpack sources
if [ ! -f opencv.zip ]; then
  swget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
fi
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake  ../opencv-master
# Build
cmake --build .
