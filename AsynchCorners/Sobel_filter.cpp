#include "Sobel_filter.hpp"

Sobel_filter::Sobel_filter(cv::Size size)
{
	m_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
	m_display_mat = cv::Mat(size, CV_64FC3, cv::Scalar(0, 0, 0));
}

constexpr double alpha = 2 * CV_PI;
constexpr double c = 0.1;

cv::Mat sobel_x_kernel = (cv::Mat_<int>(5, 5) <<
	0, 0, 0, 0, 0,
	0, -1, 0, 1, 0,
	0, -2, 0, 2, 0,
	0, -1, 0, 1, 0,
	0, 0, 0, 0, 0
	);
cv::Mat sobel_y_kernel = (cv::Mat_<int>(5, 5) <<
	0, 0, 0, 0, 0,
	0, -1, -2, -1, 0,
	0, 0, 0, 0, 0,
	0, 1, 2, 1, 0,
	0, 0, 0, 0, 0
	);

void Sobel_filter::Update(Event &event)
{
	for (int u = 0; u < 5; u++)
	{
		int x = u + event.m_x - 2;
		if (x >= 0 && x < m_mat.cols)
		{
			for (int v = 0; v < 5; v++)
			{
				int y = v + event.m_y - 2;
				if (y >= 0 && y < m_mat.rows)
				{
					cv::Vec3d previous_filter_point = m_mat.at<cv::Vec3d>(y, x);
					double timestamp_delta = event.m_timestamp - previous_filter_point[2];
					double x_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[0] + event.m_polarity * c *sobel_x_kernel.at<int>(v, u);
					double y_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[1] + event.m_polarity * c * sobel_y_kernel.at<int>(v, u);
					cv::Vec3d new_filter_point = cv::Vec3d(x_deriv, y_deriv, event.m_timestamp);
					cv::Vec3d new_display_point = cv::Vec3d(x_deriv, y_deriv, 0);
					m_mat.at<cv::Vec3d>(y, x) = new_filter_point;
					m_display_mat.at<cv::Vec3d>(y, x) = new_display_point;
				}
			}
		}
	}
}

void Sobel_filter::Update_for_display(double timestamp)
{
	for (int x = 0; x < m_mat.cols; x++)
	{
		for (int y = 0; y < m_mat.rows; y++)
		{
			cv::Vec3d previous_filter_point = m_mat.at<cv::Vec3d>(y, x);
			double timestamp_delta = timestamp - previous_filter_point[2];
			double x_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[0];
			double y_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[1];
			cv::Vec3d new_filter_point = cv::Vec3d(x_deriv, y_deriv, timestamp);
			cv::Vec3d new_display_point = cv::Vec3d(x_deriv, y_deriv, 0);
			m_mat.at<cv::Vec3d>(y, x) = new_filter_point;
			m_display_mat.at<cv::Vec3d>(y, x) = new_display_point;
		}
	}
}