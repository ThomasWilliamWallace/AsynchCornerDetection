#include "Harris_filter.hpp"

Harris_filter::Harris_filter(cv::Size size)
{
	m_mat = cv::Mat(size, CV_64FC1, cv::Scalar(0));
}

constexpr double k = 0.04;

cv::Mat gaussian_kernel = (cv::Mat_<double>(3, 3) << 1 / 16, 2 / 16, 1 / 16, 2 / 16, 4 / 16, 2 / 16, 1 / 16, 2 / 16, 1 / 16);

void Harris_filter::Update(Sobel_filter &sobel_filter, Event &event)
{
	double sum_ix2 = 0;
	double sum_iy2 = 0;
	double sum_ixy = 0;
	for (int u = 0; u < 3; u++)
	{
		int x = u + event.m_x - 1;
		if (x >= 0 && x < sobel_filter.m_mat.cols)
		{
			for (int v = 0; v < 3; v++)
			{
				int y = v + event.m_y - 1;
				if (y >= 0 && y < sobel_filter.m_mat.rows)
				{
					sum_ix2 += sobel_filter.m_mat.at<cv::Vec3d>(y, x)[0] * sobel_filter.m_mat.at<cv::Vec3d>(y, x)[0];
					sum_iy2 += sobel_filter.m_mat.at<cv::Vec3d>(y, x)[1] * sobel_filter.m_mat.at<cv::Vec3d>(y, x)[1];
					sum_ixy += sobel_filter.m_mat.at<cv::Vec3d>(y, x)[0] * sobel_filter.m_mat.at<cv::Vec3d>(y, x)[1];
				}
			}
		}
	}

	//TODO possibly add some gaussian spread here?

	double determinant = sum_ix2 * sum_iy2 - sum_ixy * sum_ixy;
	double trace = sum_ix2 + sum_iy2;
	double harris_response = (determinant - k * pow(trace, 2));

	m_mat.at<double>(event.m_y, event.m_x) = harris_response;
}