/******************************************************************************
    Modified from
    https://docs.opencv.org/4.5.0/d7/dff/tutorial_feature_homography.html

******************************************************************************/
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include "data.hpp"


using namespace std;
using namespace cv;
using namespace cv::xfeatures2d;
using namespace boost;

void pipeline(filesystem::path const image_ir_path,
             filesystem::path const image_rgb_path,
             filesystem::path const output_directory,
             uint const x1, uint const y1, 
             uint const x2, uint const y2)
{
    // Load images
    Mat source   = imageLoad(image_ir_path,  IMREAD_GRAYSCALE);
    Mat original = imageLoad(image_rgb_path, IMREAD_UNCHANGED);
    Mat destination;
    cvtColor(original, destination, COLOR_RGB2GRAY);
    
    const Size IMAGE_SIZE = original.size();

    // ROI
    Mat cropped_source = source(Range(x1, x2), Range(y1, y2));

    // Feature detection
    Ptr<SIFT> detector = SIFT::create();
    std::vector<KeyPoint> keypoints_source, keypoints_destination;
    Mat descriptors_source, descriptors_destination;
    detector->detectAndCompute( cropped_source, noArray(), keypoints_source, descriptors_source );
    detector->detectAndCompute( destination, noArray(), keypoints_destination, descriptors_destination );


    // Feature matching
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create(DescriptorMatcher::BRUTEFORCE);
    std::vector< std::vector<DMatch> > knn_matches;
    matcher->knnMatch( descriptors_source, descriptors_destination, knn_matches, 2 );

    const float ratio_thresh = 0.7f;
    std::vector<DMatch> good_matches;
    for (size_t i = 0; i < knn_matches.size(); i++)
    {
        if (knn_matches[i][0].distance < ratio_thresh * knn_matches[i][1].distance)
        {
            good_matches.push_back(knn_matches[i][0]);
        }
    }


    // Homography
    std::vector<Point2f> src;
    std::vector<Point2f> dst;
    for( size_t i = 0; i < good_matches.size(); i++ )
    {
        src.push_back( keypoints_source[ good_matches[i].queryIdx ].pt );
        dst.push_back( keypoints_destination[ good_matches[i].trainIdx ].pt );
    }
    Mat H = findHomography( src, dst, RANSAC );
    
    std::vector<Point2f> src_corners(4);
    src_corners[0] = Point2f(0, 0);
    src_corners[1] = Point2f( (float)cropped_source.cols, 0 );
    src_corners[2] = Point2f( (float)cropped_source.cols, (float)cropped_source.rows );
    src_corners[3] = Point2f( 0, (float)cropped_source.rows );
    std::vector<Point2f> dst_corners(4);

    // This will fail if not enough matches were found
    perspectiveTransform( src_corners, dst_corners, H);


    // Generate -matching-keypoints image
    Mat img_matches;
    drawMatches( cropped_source, keypoints_source, destination, keypoints_destination, good_matches, img_matches, Scalar(0, 255, 0),
                 Scalar::all(-1), std::vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

    line( img_matches, dst_corners[0] + Point2f((float)cropped_source.cols, 0),
          dst_corners[1] + Point2f((float)cropped_source.cols, 0), Scalar(255,255,255), 4 );
    line( img_matches, dst_corners[1] + Point2f((float)cropped_source.cols, 0),
          dst_corners[2] + Point2f((float)cropped_source.cols, 0), Scalar(255,255,255), 4 );
    line( img_matches, dst_corners[2] + Point2f((float)cropped_source.cols, 0),
          dst_corners[3] + Point2f((float)cropped_source.cols, 0), Scalar(255,255,255), 4 );
    line( img_matches, dst_corners[3] + Point2f((float)cropped_source.cols, 0),
          dst_corners[0] + Point2f((float)cropped_source.cols, 0), Scalar(255,255,255), 4 );

    filesystem::path output_path = filesystem::path(output_directory);
    output_path /= image_ir_path.stem();
    output_path += "-matching-keypoints";
    output_path += image_ir_path.extension();
    imageSave(img_matches, output_path);


    // Alignement
    Mat warped;
    warpPerspective(cropped_source, 
                    warped, 
                    H, 
                    IMAGE_SIZE);

    Mat mask;
    warpPerspective(Mat::ones(cropped_source.size(), CV_8U)*255, 
                    mask, 
                    H, 
                    IMAGE_SIZE); 

    // Unsafe. There has to be a better way to accomplish this
    for( int i = 0; i < warped.rows; ++i)
    {
        for( int j = 0; j < warped.cols; ++j )
        {
            if(mask.at<uchar>(i,j) > 0) {
                original.at<Vec3b>(i,j)[0] = warped.at<uchar>(i,j);
                original.at<Vec3b>(i,j)[1] = warped.at<uchar>(i,j);
                original.at<Vec3b>(i,j)[2] = warped.at<uchar>(i,j);
            }
        }
    }

    output_path = filesystem::path(output_directory);
    output_path /= image_ir_path.stem();
    output_path += "-aligned";
    output_path += image_ir_path.extension();
    imageSave(original, output_path);
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

    return 0;
}
