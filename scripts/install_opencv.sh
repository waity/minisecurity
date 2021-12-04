# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y cmake g++ wget unzip
sudo apt -y install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
# Download and unpack sources
if [ ! -f opencv.zip ]; then
  wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
  wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
fi

unzip opencv.zip
unzip opencv_contrib.zip

# Create build directory
mkdir -p build && cd build

# Configure
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D INSTALL_PYTHON_EXAMPLES=OFF \
      -D INSTALL_C_EXAMPLES=OFF \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
      -D PYTHON_EXECUTABLE=~/env/bin/python3 \
      -D BUILD_EXAMPLES=ON \
      -D WITH_CUDA=ON \
      -D WITH_CUDNN=ON \
      -D OPENCV_DNN_CUDA=ON \
      -D WITH_CUBLAS=ON \
      -D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda-10.2 \
      -D OpenCL_LIBRARY=/usr/local/cuda-10.2/lib64/libOpenCL.so \
      -D OpenCL_INCLUDE_DIR=/usr/local/cuda-10.2/include/ ../opencv-master
