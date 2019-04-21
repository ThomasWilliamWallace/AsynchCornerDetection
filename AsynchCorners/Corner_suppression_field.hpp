#pragma once
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Event.hpp"

class Corner_suppression_field
{
public:
	cv::Mat m_mat;

	Corner_suppression_field(cv::Size size);
	void Update(Event &event);
	void Update_for_display(double timestamp);
};

constexpr int suppress_scale = 5;