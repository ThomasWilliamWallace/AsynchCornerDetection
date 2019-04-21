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

constexpr double alpha = 2 * CV_PI;
constexpr double c = 0.1;

cv::Mat sobel_x_kernel = (cv::Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
cv::Mat sobel_y_kernel = (cv::Mat_<int>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);

void Event::Update_sobel_filter(Sobel_filter &sobel_filter)
{
	for (int u = 0; u < 3; u++)
	{
		int x = u + m_x - 1;
		if (x >= 0 && x < sobel_filter.m_mat.cols)
		{
			for (int v = 0; v < 3; v++)
			{
				int y = v + m_y - 1;
				if (y >= 0 && y < sobel_filter.m_mat.rows)
				{
					cv::Vec3d previous_filter_point = sobel_filter.m_mat.at<cv::Vec3d>(y, x);
					double timestamp_delta = m_timestamp - previous_filter_point[2];
					double x_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[0] + m_polarity * c *sobel_x_kernel.at<int>(v, u);
					double y_deriv = exp(-alpha * (timestamp_delta)) * previous_filter_point[1] + m_polarity * c * sobel_y_kernel.at<int>(v, u);
					cv::Vec3d new_filter_point = cv::Vec3d(x_deriv, y_deriv, m_timestamp);
					cv::Vec3d new_display_point = cv::Vec3d(x_deriv, y_deriv, 0);
					sobel_filter.m_mat.at<cv::Vec3d>(y, x) = new_filter_point;
					sobel_filter.m_display_mat.at<cv::Vec3d>(y, x) = new_display_point;
				}
			}
		}
	}
}

constexpr double k = 0.045;

cv::Mat gaussian_kernel = (cv::Mat_<double>(3, 3) << 1/16, 2/16, 1/16, 2/16, 4/16, 2/16, 1/16, 2/16, 1/16);

void Event::Update_harris_filter(Harris_filter &harris_filter, Sobel_filter &sobel_filter)
{
	double ix2 = sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[0] * sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[0];
	double iy2 = sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[1] * sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[1];
	double ixy = sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[0] * sobel_filter.m_mat.at<cv::Vec3d>(m_y, m_x)[1];

	//TODO possibly add some gaussian spread here?
					
	double determinant = ix2 * iy2 - ixy * ixy;
	double trace = ix2 + iy2;
	double harris_response = (determinant - k * trace) * 5;

	harris_filter.m_mat.at<double>(m_y, m_x) = harris_response;
}

void Event::Print_corner(Harris_filter &harris_filter, cv::Mat &display_image)
{
	if (harris_filter.m_mat.at<double>(m_y, m_x) < -0.05)
	{
		//paint corner onto display image
		cv::circle(display_image, cv::Point(m_x, m_y), 3, cv::Scalar(0, 255, 0), 1, 8, 0);
	}
}