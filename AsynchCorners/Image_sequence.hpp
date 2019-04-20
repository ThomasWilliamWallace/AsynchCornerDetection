#pragma once
#include "Image_data.hpp"
#include <string>

class Image_sequence {
public:
	std::vector<Image_data> image_data;

	Image_sequence(std::string image_sequence_path);
};