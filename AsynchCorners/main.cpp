#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

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

	std::cout << "BEGIN\n";
	if (infile.is_open()) {
		std::string line;
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
			std::cout << "timestamp=" << timestamp << "\n";
		}
		infile.close();
		std::cout << "END\n";
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}