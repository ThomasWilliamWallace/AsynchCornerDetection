#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class Image_data {
public:
	cv::Mat m_image;
	double m_timestamp;
	
	Image_data(cv::Mat image, double timestamp);
};