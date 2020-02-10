#include <iostream>
#include <opencv2/core.hpp>

#include "load.h"
#include "scanzip.h"
int main(int argc, char* argv[])
{
	if (argc < 3) return EXIT_FAILURE;

	cv::Mat position;
	cv::Mat color;
	cv::Mat flags;
	cv::Mat depth; 

	bool result = false;
	if (!strcmp("zip", argv[1]) && argc == 4)
	{
		result = load_from_bin(position, color, flags, depth, argv[2]);
		if (result)
		{
			result = save_scanzip(position, color, flags, depth, argv[3]);
		}
	}
	else if (!strcmp("unz", argv[1]) && argc == 4)
	{
		result = load_scanzip(position, color, flags, depth, argv[2]);
		if(result) result = save_scanzip(position, color, flags, depth, argv[3]);
	}

	return result ? EXIT_SUCCESS : EXIT_FAILURE;
}