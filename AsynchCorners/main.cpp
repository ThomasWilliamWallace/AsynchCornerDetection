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
	std::cout << "LOADING IMAGES" << std::endl;

	constexpr int c_imageCount = 1356;  //hardcoded to number of images in 'shapes_translation'
	cv::Mat images[c_imageCount];
	double timestamps[c_imageCount];

	std::ifstream imageListFile("cam_data/shapes_translation/images.txt");  //takes form of 'timestamp imageFileName'
	if (imageListFile.is_open()) {
		std::string line;
		int index = 0;
		while (getline(imageListFile, line)) {

			std::istringstream iss(line);

			double timestamp;
			std::string imageFileName;
			if (!(iss >> timestamp >> imageFileName)) {
				//error
				break;
			}
			std::string fullFileName = "cam_data/shapes_translation/" + imageFileName;
			const cv::String filename = fullFileName.c_str();
			images[index] = cv::imread(filename, cv::IMREAD_COLOR);
			if (images[index].empty()) // Check for invalid input
			{
				std::cout << "Could not open or find the image" << std::endl;
				return -1;
			}
			timestamps[index] = timestamp;
			index += 1;
		}
		imageListFile.close();
	}

	cv::namedWindow("Image", cv::WINDOW_AUTOSIZE); // Create a window for display.
	
	std::cout << "PROCESSING EVENT DATA" << std::endl;

	int image_index = -1;
	int next_image_index = 0;
	double image_timestamp = -1;

	std::ifstream infile("cam_data/shapes_translation/events.txt");  //takes form of 'timestamp x y polarity'

	if (infile.is_open()) {

		std::string line;
		double lastPrintedTimestamp = -999999;
		cv::Vec3b onColour = cv::Vec3b(255, 0, 0);
		cv::Vec3b offColour = cv::Vec3b(0, 0, 255);
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
				//update the printed timestamp
				std::cout << "timestamp=" << timestamp << "\n";
				lastPrintedTimestamp = timestamp;
			}

			if (timestamp > image_timestamp)
			{
				//update the displayed image
				image_index = std::min(image_index + 1, c_imageCount);
				next_image_index = std::min(next_image_index + 1, c_imageCount);
				image_timestamp = timestamps[image_index];
				cv::imshow("Image", images[image_index]); // Show our image inside it.
				cv::waitKey(1); //allow pause to display the image
			}

			if (polarity < 1)
			{
				images[next_image_index].at<cv::Vec3b>(y, x) = offColour;
			}
			else {
				images[next_image_index].at<cv::Vec3b>(y, x) = onColour;
			}

		}
		infile.close();
		std::cout << "PROCESSING COMPLETE, PROGRAM FINISHED" << std::endl;
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}