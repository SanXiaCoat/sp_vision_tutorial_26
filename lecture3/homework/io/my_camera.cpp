#include "my_camera.hpp"

myCamera::myCamera() 
{
    ret_ = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list_);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Enum devices failed!" << std::endl;
        return;
    }
  
    if (device_list_.nDeviceNum == 0) 
    {
        std::cerr << "No device found!" << std::endl;
        return;
    }

    ret_ = MV_CC_CreateHandle(&handle_, device_list_.pDeviceInfo[0]);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Create handle failed!" << std::endl;
        return;
    }

    ret_ = MV_CC_OpenDevice(handle_);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Open device failed!" << std::endl;
        return;
    }

    init();

    ret_ = MV_CC_StartGrabbing(handle_);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Start grabbing failed!" << std::endl;
        return;
    }

}

myCamera::~myCamera() 
{
    ret_ = MV_CC_StopGrabbing(handle_);
    if (ret_ != MV_OK) {
        return;
    }

    ret_ = MV_CC_CloseDevice(handle_);
    if (ret_ != MV_OK) {
        return;
    }

    ret_ = MV_CC_DestroyHandle(handle_);
    if (ret_ != MV_OK) {
        return;
    }
}

cv::Mat myCamera::read()
{


    ret_ = MV_CC_GetImageBuffer(handle_, &raw_frame_, nMsec_);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Get image buffer failed!" << std::endl;
        return cv::Mat();
    }

    cv::Mat img = transfer(raw_frame_);
    ret_ = MV_CC_FreeImageBuffer(handle_, &raw_frame_);
    if (ret_ != MV_OK) 
    {
        std::cerr << "Free image buffer failed!" << std::endl;
    }
    return img;
}

void myCamera::init()
{
    MV_CC_SetEnumValue(handle_, "BalanceWhiteAuto", MV_BALANCEWHITE_AUTO_CONTINUOUS);
    MV_CC_SetEnumValue(handle_, "ExposureAuto", MV_EXPOSURE_AUTO_MODE_OFF);
    MV_CC_SetEnumValue(handle_, "GainAuto", MV_GAIN_MODE_OFF);
    MV_CC_SetFloatValue(handle_, "ExposureTime", exposure_time_);
    MV_CC_SetFloatValue(handle_, "Gain", gain_);
    MV_CC_SetFrameRate(handle_, frame_rate_);
}

cv::Mat myCamera::transfer(const MV_FRAME_OUT& raw)
{
    MV_CC_PIXEL_CONVERT_PARAM cvt_param;
    cv::Mat img(cv::Size(raw.stFrameInfo.nWidth, raw.stFrameInfo.nHeight), CV_8U, raw.pBufAddr);

    cvt_param.nWidth = raw.stFrameInfo.nWidth;
    cvt_param.nHeight = raw.stFrameInfo.nHeight;

    cvt_param.pSrcData = raw.pBufAddr;
    cvt_param.nSrcDataLen = raw.stFrameInfo.nFrameLen;
    cvt_param.enSrcPixelType = raw.stFrameInfo.enPixelType;

    cvt_param.pDstBuffer = img.data;
    cvt_param.nDstBufferSize = img.total() * img.elemSize();
    cvt_param.enDstPixelType = PixelType_Gvsp_BGR8_Packed;

    auto pixel_type = raw.stFrameInfo.enPixelType;
    const static std::unordered_map<MvGvspPixelType, cv::ColorConversionCodes> type_map = {
      {PixelType_Gvsp_BayerGR8, cv::COLOR_BayerGR2RGB},
      {PixelType_Gvsp_BayerRG8, cv::COLOR_BayerRG2RGB},
      {PixelType_Gvsp_BayerGB8, cv::COLOR_BayerGB2RGB},
      {PixelType_Gvsp_BayerBG8, cv::COLOR_BayerBG2RGB}};
    cv::cvtColor(img, img, type_map.at(pixel_type));
    
    return img;
}


