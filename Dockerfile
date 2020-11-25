FROM ubuntu:xenial

RUN apt-get update && apt-get install -y \
    git \
    build-essential \
    libboost-filesystem-dev \
    curl libssl-dev libcurl4-openssl-dev \
    zlib1g-dev \
    wget

WORKDIR /tmp
RUN wget https://cmake.org/files/v3.10/cmake-3.10.3.tar.gz
RUN tar -xzvf cmake-3.10.3.tar.gz
WORKDIR /tmp/cmake-3.10.3
RUN ./bootstrap --system-curl && make && make install

WORKDIR /
RUN git clone https://github.com/opencv/opencv_contrib.git
RUN git clone https://github.com/opencv/opencv.git
WORKDIR /opencv_contrib
RUN git checkout 4.5.0
WORKDIR /opencv
RUN git checkout 4.5.0

RUN mkdir -p build
RUN cmake -H. -Bbuild \
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
RUN cmake --build build --target install -- -j $(nproc)
# on Travis, use the following command instead
# RUN sudo env "PATH=$PATH" cmake --build build --target install -- -j $(nproc)

WORKDIR /swdev
ENV LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:/usr/local/lib"
COPY . .
# unlike on Travis instances, here the build directory will be copied to the image if it exists
#TODO: Prevent build directory and other uneeded files to be copied to the image
RUN rm -r build || mkdir -p build
RUN cmake -H. -Bbuild
RUN cmake --build build --config Release --target all -- -j $(nproc)
CMD ./build/tests/data_test