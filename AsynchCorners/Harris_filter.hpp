#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

class Harris_filter
{
public:
	cv::Mat m_mat;

	Harris_filter(cv::Size size);
};