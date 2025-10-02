#include "io/my_camera.hpp"
#include "tasks/yolo.hpp"
#include "opencv2/opencv.hpp"
#include "tools/img_tools.hpp"

int main()
{
    // 初始化相机、yolo类
    myCamera cam;
    auto yolo = auto_aim::YOLO("../configs/yolo.yaml", true);
    while (1) {
        // 调用相机读取图像
        cv::Mat img = cv::imread("../../lecture2/img/test_1.jpg");
        if (img.empty()) {
            continue;
        }


        // 调用yolo识别装甲板
        std::list<auto_aim::Armor> armors = yolo.detect(img);

        // 绘制每个装甲板的四个关键点为红色闭合矩形
        for (const auto& armor : armors) 
        {
            tools::draw_points(img, armor.points, cv::Scalar(0, 0, 255), 2);

            std::string color_str = auto_aim::COLORS[static_cast<int>(armor.color)];
            std::string name_str = auto_aim::ARMOR_NAMES[static_cast<int>(armor.name)];

            cv::Point text_start(armor.points[0].x, armor.points[0].y - 20);  
            cv::Point name_start(text_start.x, text_start.y + 20);  

            tools::draw_text(img, color_str + name_str, text_start, cv::Scalar(255, 0, 0));
        }
        
        

        // 显示图像
        cv::resize(img, img , cv::Size(640, 480));
        cv::imshow("img", img);
        if (cv::waitKey(0) == 'q') {
            break;
        }
    }

    return 0;
}