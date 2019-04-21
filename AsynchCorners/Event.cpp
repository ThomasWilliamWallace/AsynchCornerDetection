#include "Event.hpp"
#include <iostream>
#include <cmath>
#include <opencv2/imgproc.hpp>

const cv::Vec3b on_colour = cv::Vec3b(0, 0, 255);
const cv::Vec3b off_colour = cv::Vec3b(255, 0, 0);

Event::Event(std::istringstream &iss)
{
	//read event from file
	if (!(iss >> m_timestamp >> m_x >> m_y >> m_polarity)) {
		std::cout << "ERROR: Could not parse line from event file" << std::endl;
		throw - 1;
	}
	m_polarity = m_polarity ? 1 : -1;
}

void Event::Print_event(cv::Mat &display_image)
{
	//paint event onto display image
	if (m_polarity > 0)
	{
		display_image.at<cv::Vec3b>(m_y, m_x) = on_colour;
	}
	else {
		display_image.at<cv::Vec3b>(m_y, m_x) = off_colour;
	}
}

/*
void Event::Print_corner(Harris_filter &harris_filter, cv::Mat &display_image)
{
	if (harris_filter.m_mat.at<double>(m_y, m_x) < -0.5)
	{
		//paint corner onto display image
		cv::circle(display_image, cv::Point(m_x, m_y), 3, cv::Scalar(0, 255, 0), 1, 8, 0);
	}
}*/