#pragma once
#ifndef DATA_HPP
#define DATA_HPP

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


cv::Mat imageLoad(std::string const path, cv::ImreadModes const read_mode);
bool imageSave(cv::Mat const image, std::string const path);

#endif // DATA_HPP