#include <fstream>
#include <string>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Event.hpp"
#include "Image_sequence.hpp"

double UpdateDisplay(double timestamp, double last_printed_timestamp, cv::Mat display_image, Image_sequence &image_sequence, int current_image_index)
{
	if (timestamp - last_printed_timestamp > 0.01)
	{
		//update the displayed image and printed timestamp
		cv::imshow("Video", display_image);
		display_image = image_sequence.m_image_data[current_image_index].m_image.clone();
		//std::cout << "timestamp=" << timestamp << "\n";
		cv::waitKey(1); //trigger the display of the image
		return timestamp;
	}
}

int main(int argc, char** argv)
{
	std::cout << "LOADING IMAGES" << std::endl;
	std::string image_sequence_path = "cam_data/shapes_translation/images.txt";
	Image_sequence image_sequence(image_sequence_path);

	cv::namedWindow("Video", cv::WINDOW_AUTOSIZE); // Create a window for display.
	
	std::cout << "PROCESSING EVENT DATA" << std::endl;
	int current_image_index = 0;
	int next_image_index = 1;
	double image_timestamp = -1;

	std::ifstream infile("cam_data/shapes_translation/events.txt");  //takes form of 'timestamp x y polarity'

	if (infile.is_open()) {

		std::string line;
		double last_printed_timestamp = -999999;
		cv::Mat display_image = image_sequence.m_image_data[0].m_image.clone();
		while (getline(infile, line)) {

			std::istringstream iss(line);

			Event event(iss);

			if (event.m_timestamp > image_timestamp)
			{
				//select next image for display
				current_image_index = next_image_index;
				next_image_index = std::min(next_image_index + 1, static_cast<int>(image_sequence.m_image_data.size()));
				display_image = image_sequence.m_image_data[current_image_index].m_image.clone();
				image_timestamp = image_sequence.m_image_data[next_image_index].m_timestamp;
			}

			event.print(display_image);

			last_printed_timestamp = UpdateDisplay(
										event.m_timestamp,
										last_printed_timestamp,
										display_image,
										image_sequence,
										current_image_index
									);

		}
		infile.close();
		std::cout << "PROCESSING COMPLETE, PROGRAM FINISHED" << std::endl;
		cv::waitKey(0); // Wait for a keystroke in the window
	}

	return 0;
}