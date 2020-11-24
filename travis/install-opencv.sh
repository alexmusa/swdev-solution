#!/bin/sh

cd /tmp
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout 4.5.0

# Configure
mkdir -p build
cmake -H. -Bbuild \
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

cd /home/travis/build/alexmusa/swdev-solution