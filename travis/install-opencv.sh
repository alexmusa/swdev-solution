#!/bin/sh

cd /tmp
git clone https://github.com/opencv/opencv_contrib.git
git clone https://github.com/opencv/opencv.git
cd /tmp/opencv_contrib
git checkout 4.5.0
cd /tmp/opencv
git checkout 4.5.0

# Configure
mkdir -p build
cmake -H. -Bbuild \
-DOPENCV_ENABLE_NONFREE=ON \
-DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules \
-DBUILD_opencv_videoio=OFF \
-DBUILD_opencv_video=OFF \
-DBUILD_opencv_ts=OFF \
-DBUILD_opencv_stitching=OFF \
-DBUILD_opencv_python_tests=OFF \
-DBUILD_opencv_python_bindings_generator=OFF \
-DBUILD_opencv_python3=OFF \
-DBUILD_opencv_java_bindings_generator=OFF \
-DBUILD_opencv_highgui=OFF \
-DBUILD_opencv_gapi=OFF \
-DBUILD_opencv_ml=OFF \
-DBUILD_opencv_js=OFF

# Build and install
sudo env "PATH=$PATH" cmake --build build --target install -- -j $(nproc)