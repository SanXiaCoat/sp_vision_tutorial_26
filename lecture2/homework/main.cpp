#include <iostream>
#include "tools.hpp"

//主函数
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input_image>\n";
        return 1;
    }
    std::string inPath = argv[1];
    std::cout << "Input image path: " << inPath;
    
    // 读取图片
    cv::Mat bgr_img = cv::imread(inPath);
    if (bgr_img.empty())
    {
        std::cout << "fail to load image" << std::endl;
        return -1;
    }

    //缩放图片
    int offsetX = 0, offsetY = 0;
    double proportion = 0.0;
    cv::Mat bgr_img_resized;
    resizeImg(bgr_img, bgr_img_resized, cv::Size(16, 16), &offsetX, &offsetY, &proportion);

    //fmt输出放缩比例，图像偏移距离
    fmt::print("proportion: {:.4f}, offsetX: {}, offsetY: {}\n", proportion, offsetX, offsetY);

    //显示图片
    cv::imshow("bgr_img", bgr_img_resized);

    cv::waitKey(0);
}