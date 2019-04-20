#include "Event.hpp"
#include <iostream>

const cv::Vec3b on_colour = cv::Vec3b(0, 0, 255);
const cv::Vec3b off_colour = cv::Vec3b(255, 0, 0);

Event::Event(std::istringstream &iss)
{
	//read event from file
	if (!(iss >> m_timestamp >> m_x >> m_y >> m_polarity)) {
		std::cout << "Could not parse line from event file" << std::endl;
		throw - 1;
	}
}

void Event::print(cv::Mat &display_image)
{
	//paint event onto display image
	if (m_polarity < 1)
	{
		display_image.at<cv::Vec3b>(m_y, m_x) = off_colour;
	}
	else {
		display_image.at<cv::Vec3b>(m_y, m_x) = on_colour;
	}
}