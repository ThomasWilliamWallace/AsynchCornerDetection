#include "Corner_suppression_field.hpp"

Corner_suppression_field::Corner_suppression_field(cv::Size size)
{
	m_mat = cv::Mat(size.height / suppress_scale , size.width / suppress_scale, CV_64FC3, cv::Scalar(5, 0, 0));
}

constexpr double alpha2 = 10 * CV_PI;
constexpr double c2 = 1;

void Corner_suppression_field::Update(Event &event)
{
	cv::Vec3d previous_filter_point = m_mat.at<cv::Vec3d>(event.m_y/ suppress_scale, event.m_x/ suppress_scale);  //TODO change to 2 channels?
	double timestamp_delta = event.m_timestamp - previous_filter_point[2];
	double corner_suppression = exp(-alpha2 * timestamp_delta) * previous_filter_point[0] + c2;
	m_mat.at<cv::Vec3d>(event.m_y / suppress_scale, event.m_x / suppress_scale) = cv::Vec3d(corner_suppression, 0, event.m_timestamp);
}

void Corner_suppression_field::Update_for_display(double timestamp)
{
	for (int x = 0; x < m_mat.cols; x++)
	{
		for (int y = 0; y < m_mat.rows; y++)
		{
			cv::Vec3d previous_filter_point = m_mat.at<cv::Vec3d>(y, x);
			double timestamp_delta = timestamp - previous_filter_point[2];
			double x_deriv = exp(-alpha2 * (timestamp_delta)) * previous_filter_point[0];
			double y_deriv = exp(-alpha2 * (timestamp_delta)) * previous_filter_point[1];
			cv::Vec3d new_filter_point = cv::Vec3d(x_deriv, y_deriv, timestamp);
			cv::Vec3d new_display_point = cv::Vec3d(x_deriv, y_deriv, 0);
			m_mat.at<cv::Vec3d>(y, x) = new_filter_point;
		}
	}
}