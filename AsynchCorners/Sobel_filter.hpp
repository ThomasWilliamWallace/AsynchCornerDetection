#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Event.hpp"

class Sobel_filter {
public:
	cv::Mat m_mat;
	cv::Mat m_display_mat;

	Sobel_filter(cv::Size size);
	void Update(Event &event);
	void Update_for_display(double timestamp);
};