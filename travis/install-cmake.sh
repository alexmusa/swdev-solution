#!/bin/sh

cd /tmp
wget https://cmake.org/files/v3.10/cmake-3.10.3.tar.gz
tar -xzvf cmake-3.10.3.tar.gz

cd /tmp/cmake-3.10.3
./bootstrap && make && make install