#ifndef scan_zip_h
#define scan_zip_h

namespace cv
{
	class Mat;
}

bool save_scanzip(const cv::Mat& position, const cv::Mat& color, const cv::Mat& flags, const cv::Mat& depth, const char* zip_file);
bool load_scanzip(cv::Mat& position, cv::Mat& color, cv::Mat& flags, cv::Mat& depth, const char* zip_file);

//zip_file 打开或保存的文件名，扩展名.zip，如果不是，实现会增加.zip
//position 点云坐标, 在zip文档中保存为position.yml, Mat的元素格式是 CV_32FC3 
//color    点云颜色，在zip文档中保存为color.bmp，彩色图片Mat元素格式是 CV_8UC3 或 CV_8UC4， 灰白图片Mat元素格式是 CV_8UC1
//flags    标志，在zip文档中保存为flags.bmp， Mat的元素格式是 CV_8UC1
//depth    深度图，在zip文档中保存为depth.bmp，Mat的元素格式是 CV_8UC1

//加载的过程需要传入未初始化的相应Mat，如果文件加载成功，数据会填充对应的Mat

#endif // scan_zip_h