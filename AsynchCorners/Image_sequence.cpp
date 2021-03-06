#include "Image_sequence.hpp"
#include <opencv2/imgcodecs.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

Image_sequence::Image_sequence(std::string cam_data_path)
{
	std::string image_sequence_path = cam_data_path + "images.txt";
	std::ifstream image_list_file(image_sequence_path.c_str());
	if (image_list_file.is_open()) {
		std::string line;
		int index = 0;
		while (getline(image_list_file, line)) {

			std::istringstream iss(line);

			double timestamp;
			std::string image_filename;
			if (!(iss >> timestamp >> image_filename)) {  // each line takes the form of 'timestamp imageFileName'
				std::cout << "ERROR: Could not parse line from images file" << std::endl;
				throw - 1;
			}
			std::string full_filename = cam_data_path + image_filename;
			const cv::String filename = full_filename.c_str();
			m_image_data.emplace_back(cv::imread(filename, cv::IMREAD_COLOR), timestamp);
			if (m_image_data[index].m_image.empty()) // Check for invalid input
			{
				std::cout << "ERROR: Could not open or find the image" << std::endl;
				throw - 1;
			}
			index += 1;
		}
		image_list_file.close();
	}
}