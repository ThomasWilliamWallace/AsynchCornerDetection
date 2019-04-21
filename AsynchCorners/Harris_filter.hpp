#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Sobel_filter.hpp"
#include "Event.hpp"

class Harris_filter
{
public:
	cv::Mat m_mat;

	Harris_filter(cv::Size size);
	void Update(Sobel_filter &sobel_filter, Event &event);
	//void Update2(Sobel_filter &sobel_filter, double timestamp);
};