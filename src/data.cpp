#include <string>
#include "data.hpp"


using namespace std;
using namespace cv;
using namespace boost;

Mat imageLoad(filesystem::path const path, cv::ImreadModes const read_mode)
{
    return imread(path.string(), read_mode);
}

bool imageSave(Mat const image, filesystem::path const path)
{
    return imwrite(path.string(), image);
}