#pragma once
#include <opencv2/core.hpp>
#include <sstream>
#include "Sobel_filter.hpp"

class Event {
public:
	double m_timestamp;
	int m_x;
	int m_y;
	int m_polarity;

	Event(std::istringstream &iss);
	void Print(cv::Mat &display_image);
	void Update_filter(Sobel_filter &sobel_filter);
};