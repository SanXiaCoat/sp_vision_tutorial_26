#ifndef MY_CAMERA_HPP
#define MY_CAMERA_HPP

#include "hikrobot/include/MvCameraControl.h"
#include <opencv2/opencv.hpp>

class myCamera 
{
public:
    myCamera();
    ~myCamera();
    cv::Mat read();
private:
    int ret_ = MV_OK;
    void* handle_ = nullptr;
    MV_CC_DEVICE_INFO_LIST device_list_;
    MV_FRAME_OUT raw_frame_;
    bool is_ok_ = false;
    float exposure_time_ = 10000.0;
    float gain_ = 20.0;
    int frame_rate_ = 60;
    unsigned int nMsec_ = 100;
    void init();
    cv::Mat transfer(const MV_FRAME_OUT& raw);

};


#endif // MY_CAMERA_HPP
