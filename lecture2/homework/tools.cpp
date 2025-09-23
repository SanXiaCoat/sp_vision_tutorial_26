#include "tools.hpp"

// ====== 函数定义 ======
void resizeImg (const cv::Mat &srcIMG, cv::Mat &dstIMG, const cv::Size &size, int* offsetX, int* offsetY, double* proportion)
{
    // 计算缩放比例
    *proportion = std::min(static_cast<double>(size.width) / srcIMG.cols,static_cast<double>(size.height) / srcIMG.rows);

    // 计算新的尺寸
    int newWidth = static_cast<int>(srcIMG.cols * *proportion);
    int newHeight = static_cast<int>(srcIMG.rows * *proportion);

    // 计算偏移量
    *offsetX = (size.width - newWidth) / 2;
    *offsetY = (size.height - newHeight) / 2;

    // 输出图像初始化(填充黑色)
    dstIMG = cv::Mat::zeros(size, srcIMG.type());

    // 缩放图像
    cv::Mat resizedImg;
    cv::resize(srcIMG, resizedImg, cv::Size(newWidth, newHeight));

    // 将缩放后的图像粘贴到输出图像中
    resizedImg.copyTo(dstIMG(cv::Rect(*offsetX, *offsetY, newWidth, newHeight)));
    
}