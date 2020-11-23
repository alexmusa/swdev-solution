#include <string>
#include "data.hpp"


using namespace std;
using namespace cv;
using namespace boost;

Mat imageLoad(filesystem::path const path, cv::ImreadModes const read_mode)
{
    // TODO: If the image cannot be read (because of missing file, improper 
    // permissions, unsupported or invalid format), the function returns an 
    // empty matrix ( Mat::data==NULL ).
    return imread(path.string(), read_mode);
}

bool imageSave(Mat const image, filesystem::path const path)
{
    return imwrite(path.string(), image);
}