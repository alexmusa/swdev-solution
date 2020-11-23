#include <string>
#include <gtest/gtest.h>
#include "data.hpp"

using namespace std;
using namespace cv;
using namespace boost;

TEST(DataTest, CanLoadDataset) { 
    filesystem::path img1 = filesystem::current_path() / filesystem::path("tests/datasets/hill-ir-rot-0007.png");
    filesystem::path img2 = filesystem::current_path() / filesystem::path("tests/datasets/hill-ir-rot-0007-dirty.png");
 
    Mat image1 = imageLoad(img1, IMREAD_UNCHANGED);
    Mat image2 = imageLoad(img2, IMREAD_UNCHANGED);

    Size size = image1.size();
    Mat result = Mat(size, CV_8U);
    compare(image1, image2, result, CMP_NE);
    
    // TODO: Loop all channels
    Mat channel = Mat(size, CV_8U);
    extractChannel(result, channel, 0);

    EXPECT_TRUE (countNonZero(channel) > 0);
}

TEST(DataTest, SaveAndLoad) {
    filesystem::path src = filesystem::current_path() / filesystem::path("tests/datasets/hill-rgb-0007.png");
    filesystem::path dst = filesystem::current_path() / filesystem::path("build/Testing/Temporary/hill-rgb-0007-saved.png");
    
    Mat image = imageLoad(src, IMREAD_UNCHANGED);
    imageSave(image, dst);

    // TODO: Replace with a bit per bit comparaison? another image reader?
    Mat image_source      = imread(src.string(), IMREAD_UNCHANGED);
    Mat image_destination = imread(dst.string(), IMREAD_UNCHANGED);


    Size size = image.size();
    Mat result = Mat(size, CV_8U);
    compare(image_source, image_destination, result, CMP_NE);

    // TODO: Loop all channels
    Mat channel = Mat(size, CV_8U);
    extractChannel(result, channel, 0);

    EXPECT_FALSE (countNonZero(channel) >	0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}