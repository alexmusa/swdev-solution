#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include "data.hpp"


using namespace std;
using namespace cv;
using namespace boost;

void pipeline(filesystem::path const image_ir_path,
             filesystem::path const image_rgb_path,
             filesystem::path const output_directory,
             uint const x1, uint const y1, 
             uint const x2, uint const y2)
{

    filesystem::path output_path = filesystem::path(output_directory);
    output_path /= image_rgb_path.stem();
    output_path += "-aligned";
    output_path += image_rgb_path.extension();

    // filesystem::path output_path = filesystem::path(output_directory);
    // output_path /= image_rgb_path.stem();
    // output_path += "-matching-keypoints";
    // output_path += image_rgb_path.extension();
    
    Mat image = imageLoad(image_rgb_path, IMREAD_UNCHANGED);
    imageSave(image, output_path);
}

int main(int argc, char *argv[]){
    // TODO: Handle arguments
    filesystem::path image_ir_path    = filesystem::path(argv[1]);
    filesystem::path image_rgb_path   = filesystem::path(argv[2]);
    filesystem::path output_directory = filesystem::path(argv[3]);
    uint x1 = stoul(string(argv[4]), nullptr, 0);
    uint y1 = stoul(string(argv[5]), nullptr, 0);
    uint x2 = stoul(string(argv[6]), nullptr, 0);
    uint y2 = stoul(string(argv[7]), nullptr, 0);

    

    pipeline(image_ir_path, image_rgb_path, output_directory, x1, y1, x2, y2);
}
