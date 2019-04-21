#include "Harris_filter.hpp"

Harris_filter::Harris_filter(cv::Size size)
{
	m_mat = cv::Mat(size, CV_64FC1, cv::Scalar(0));
}