#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iomanip>
#include <vector>
#include "Event.hpp"
#include "Image_data.hpp"

int main(int argc, char** argv)
{
	std::cout << "LOADING IMAGES" << std::endl;

	std::vector<Image_data> image_data;

	std::ifstream image_list_file("cam_data/shapes_translation/images.txt");  //takes form of 'timestamp imageFileName'
	if (image_list_file.is_open()) {
		std::string line;
		int index = 0;
		while (getline(image_list_file, line)) {

			std::istringstream iss(line);

			double timestamp;
			std::string image_filename;
			if (!(iss >> timestamp >> image_filename)) {
				//error
				break;
			}
			std::string full_filename = "cam_data/shapes_translation/" + image_filename;
			const cv::String filename = full_filename.c_str();
			image_data.emplace_back(cv::imread(filename, cv::IMREAD_COLOR), timestamp);
			if (image_data[index].m_image.empty()) // Check for invalid input
			{
				std::cout << "Could not open or find the image" << std::endl;
				return -1;
			}
			index += 1;
		}
		image_list_file.close();
	}

	cv::namedWindow("Video", cv::WINDOW_AUTOSIZE); // Create a window for display.
	
	std::cout << "PROCESSING EVENT DATA" << std::endl;

	int current_image_index = 0;
	int next_image_index = 1;
	double image_timestamp = -1;

	std::ifstream infile("cam_data/shapes_translation/events.txt");  //takes form of 'timestamp x y polarity'

	if (infile.is_open()) {

		std::string line;
		double last_printed_timestamp = -999999;
		cv::Mat display_image = image_data[0].m_image.clone();
		while (getline(infile, line)) {

			std::istringstream iss(line);

			Event event(iss);

			if (event.m_timestamp > image_timestamp)
			{
				//select next image for display
				current_image_index = next_image_index;
				next_image_index = std::min(next_image_index + 1, static_cast<int>(image_data.size()));
				display_image = image_data[current_image_index].m_image.clone();
				image_timestamp = image_data[next_image_index].m_timestamp;
			}

			event.print(display_image);

			if (event.m_timestamp - last_printed_timestamp > 0.01)
			{
				//update the displayed image and printed timestamp
				cv::imshow("Video", display_image);
				display_image = image_data[current_image_index].m_image.clone();
				//std::cout << "timestamp=" << timestamp << "\n";
				last_printed_timestamp = event.m_timestamp;
				cv::waitKey(1); //trigger the display of the image
			}

		}
		infile.close();
		std::cout << "PROCESSING COMPLETE, PROGRAM FINISHED" << std::endl;
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}