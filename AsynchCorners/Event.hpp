#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <sstream>

class Event {
public:
	double timestamp;
	int x;
	int y;
	int polarity;

	Event(std::istringstream &iss);
	void print(cv::Mat &display_image);
};