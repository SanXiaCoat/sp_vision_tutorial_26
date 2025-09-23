#ifndef HOMEWORK_TOOLS_HPP
#define HOMEWORK_TOOLS_HPP

#include <iostream>
#include <opencv2/opencv.hpp>
#include <fmt/format.h>

// ====== 函数声明 ======
void resizeImg (const cv::Mat &srcIMG, cv::Mat &dstIMG, const cv::Size &size, int* offsetX, int* offsetY, double* proportion);


#endif // HOMEWORK_TOOLS_HPP