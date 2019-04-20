#pragma once
#include <opencv2/core.hpp>
#include <sstream>

class Event {
public:
	double m_timestamp;
	int m_x;
	int m_y;
	int m_polarity;

	Event(std::istringstream &iss);
	void print(cv::Mat &display_image);
};