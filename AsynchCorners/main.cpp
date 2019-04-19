#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iomanip>

int main(int argc, char** argv)
{
	std::ifstream infile("cam_data/shapes_translation/events.txt");  //takes form of 'timestamp x y polarity'

	cv::Mat image;
	image = cv::imread("cam_data/shapes_translation/images/frame_00000000.png", cv::IMREAD_COLOR); // Read image
	if (image.empty()) // Check for invalid input
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}
	cv::namedWindow("Image", cv::WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Image", image); // Show our image inside it.
	cv::waitKey(1); //allow pause to display the image

	std::cout << "LOADING IMAGES" << std::endl;
	constexpr int c_imageCount = 1356;  //hardcoded to number of images in 'shapes_translation'
	cv::Mat images[c_imageCount];
	double timestamps[c_imageCount];
	for (int i=0; i < c_imageCount; i++)
	{
		std::stringstream ss;
		ss << "cam_data/shapes_translation/images/frame_" << std::setfill('0') << std::setw(8) << i << ".png";
		const cv::String filename = ss.str().c_str();
		images[i] = cv::imread(filename, cv::IMREAD_COLOR);
	}

	int image_index = 0;
	double image_timestamp = -1;

	std::cout << "DISPLAYING VIDEO" << std::endl;
	for (int i = 0; i < c_imageCount; i++) {
		imshow("Image", images[i]); // Show our image inside it.
		cv::waitKey(1); //allow pause to display the image
	}

	std::cout << "PROCESSING EVENT DATA" << std::endl;
	if (infile.is_open()) {
		std::string line;
		double lastPrintedTimestamp = -999999;
		while (getline(infile, line)) {

			std::istringstream iss(line);

			double timestamp;
			int x;
			int y;
			int polarity;
			if (!(iss >> timestamp >> x >> y >> polarity)) {
				//error
				break;
			}
			if (timestamp - lastPrintedTimestamp > 0.1)
			{
				std::cout << "timestamp=" << timestamp << "\n";
				lastPrintedTimestamp = timestamp;
			}
		}
		infile.close();
		std::cout << "PROCESSING COMPLETE, PROGRAM FINISHED" << std::endl;
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}