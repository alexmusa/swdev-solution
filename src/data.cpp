#include <string>
#include "data.hpp"


using namespace std;
using namespace cv;

Mat imageLoad(string const path, ImreadModes const read_mode)
{
    return imread(path, read_mode);
}

bool imageSave(Mat const image, string const path)
{
    return imwrite(path, image);
}