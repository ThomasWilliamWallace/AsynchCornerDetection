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
	Event(int x, int y, int polarity, double timestamp);
	void Print_event(cv::Mat &display_image);
};