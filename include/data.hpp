#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <boost/filesystem.hpp>



cv::Mat imageLoad(boost::filesystem::path const path, cv::ImreadModes const read_mode);
bool imageSave(cv::Mat const image, boost::filesystem::path const path);

#endif // DATA_HPP