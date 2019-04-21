#include "Sobel_filter.hpp"

Sobel_filter::Sobel_filter(cv::Size size)
{
	m_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
	m_display_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
}