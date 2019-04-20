#include "Event.hpp"

const cv::Vec3b on_colour = cv::Vec3b(0, 0, 255);
const cv::Vec3b off_colour = cv::Vec3b(255, 0, 0);

void Event::print(cv::Mat &display_image)
{
	//paint event onto display image
	if (polarity < 1)
	{
		display_image.at<cv::Vec3b>(y, x) = off_colour;
	}
	else {
		display_image.at<cv::Vec3b>(y, x) = on_colour;
	}
}