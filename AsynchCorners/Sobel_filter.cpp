#include "Sobel_filter.hpp"

Sobel_filter::Sobel_filter(cv::Size size)
{
	//m_x_deriv = cv::Mat(size, CV_32FC1, cv::Scalar(0));  //TODO combine x and y into one 2 channel mat. Maybe add timestamp as the third channel.
	//m_y_deriv = cv::Mat(size, CV_32FC1, cv::Scalar(0));
	//m_most_recent_timestamps = cv::Mat(size, CV_32FC1, cv::Scalar(0));

	m_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
	m_display_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
}