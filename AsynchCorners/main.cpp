#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
	std::ifstream infile("cam_data/shapes_translation/events.txt");  //takes form of 'timestamp x y polarity'

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
		system("pause");
	}

	return 0;
}