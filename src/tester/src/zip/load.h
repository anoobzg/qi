#ifndef matzip_load_h
#define matzip_load_h

namespace cv
{
	class Mat;
}

bool load_from_bin(cv::Mat& position, cv::Mat& color, cv::Mat& flags, cv::Mat& depth, const char* bin_file);

#endif // matzip_load_h