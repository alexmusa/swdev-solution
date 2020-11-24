# swdev-solution
[![Build Status](https://travis-ci.com/alexmusa/swdev-solution.svg?branch=main)](https://travis-ci.com/alexmusa/swdev-solution)

## Python prototype

[view on Google Colab](https://colab.research.google.com/drive/1C-zI13NTnUO7Os1E7_BNffgajfaj97-n?usp=sharing)

## C++ application

The program can be built using CMake
```
mkdir -p build
cmake -H. -Bbuild
cmake --build build --config Release --target all -- -j $(nproc)
```

On Debian-based distributions, the following the following packages can be installed if needed:
```
sudo apt update && sudo apt install libboost-filesystem-dev
```

The program requires OpenCV as well as some OpenCV extra modules. Instructions to install these modules can be found [here](https://docs.opencv.org/4.5.0/d7/d9f/tutorial_linux_install.html).

A Docker image containing the program can also be built by using the script `./build-docker.sh`. The image build process might be quite long as it compile both CMake and the OpenCV libraries.

This github repository can also be forked and added to your Travis CI account.

### Usage

```
main <source_image> <destination_image> <output_directory> <x1> <y1> <x2> <y2>
```
The program has absolutly no error handling at all and does not sanitize arguments. 
It expects absolute paths to the source and destination images. 
The output directory must be existing. 
(x1;y1) and (x2;y2) are the top left and bottom right corner of the Region of Interest on the source image.

To run it in Docker use the following command with the appropriate bind mounts (`-v <host_dir>:<container_dir>`) 
```
docker run alexmusa/swdev:debug ./build/main <source_image> <destination_image> <output_directory> <x1> <y1> <x2> <y2>
```

## Tests

There is only one unit/intergration test so far. I can be run using the executable `./build/tests/data_test` or simply by running the Docker container.

[## Improvements](doc/PossibleImprovements.md)
