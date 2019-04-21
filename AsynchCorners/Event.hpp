#pragma once
#include <opencv2/core.hpp>
#include <sstream>
#include "Sobel_filter.hpp"
#include "Harris_filter.hpp"

class Event {
public:
	double m_timestamp;
	int m_x;
	int m_y;
	int m_polarity;

	Event(std::istringstream &iss);
	void Print_event(cv::Mat &display_image);
	void Print_corner(Harris_filter &harris_filter, cv::Mat &display_image);
	void Update_sobel_filter(Sobel_filter &sobel_filter);
	void Update_harris_filter(Harris_filter &harris_filter, Sobel_filter &sobel_filter);
};