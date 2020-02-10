#include "load.h"
#include <fstream>
#include <vector>
#include <opencv2/core.hpp>

void load_cloud(cv::Mat& position, cv::Mat& flags, std::fstream& in)
{
	int m_width;
	int m_height;
	int m_vertex_size;
	std::vector<int> m_flags;
	std::vector<float> m_positions;
	std::vector<unsigned char> m_colors;

	in.read((char*)(&m_width), sizeof(int));
	in.read((char*)(&m_height), sizeof(int));
	in.read((char*)(&m_vertex_size), sizeof(int));
	int flags_size = 0;
	in.read((char*)&flags_size, sizeof(int));
	if (flags_size)
	{
		m_flags.resize(flags_size);
		in.read((char*)(&m_flags.at(0)), flags_size * sizeof(int));
	}

	int position_size = 0;
	in.read((char*)&position_size, sizeof(int));
	if (position_size)
	{
		m_positions.resize(position_size);
		in.read((char*)(&m_positions.at(0)), position_size * sizeof(float));
	}
	int color_size = 0;
	in.read((char*)&color_size, sizeof(int));
	if (color_size)
	{
		m_colors.resize(color_size);
		in.read((char*)(&m_colors.at(0)), color_size * sizeof(unsigned char));
	}

	position.create(m_height, m_width, CV_32FC3);
	flags.create(m_height, m_width, CV_8UC1);
	for (int i = 0; i < m_width; ++i)
	{
		for (int j = 0; j < m_height; ++j)
		{
			int index = j * m_width + i;
			int cindex = m_flags.at(index);
			
			unsigned char* f = flags.ptr<unsigned char>(j, i);
			*f = cindex >= 0 ? 255 : 0;
			if (cindex >= 0)
			{
				float* p = &m_positions.at(3 * cindex);
				float* pp = (float*)position.ptr(j, i);
				memcpy(pp, p, 3 * sizeof(float));
			}
		}
	}
}

void load_mat(cv::Mat& mat, std::fstream& in)
{
	int m_width;
	int m_height;
	std::vector<unsigned char> m_data;

	in.read((char*)(&m_width), sizeof(int));
	in.read((char*)(&m_height), sizeof(int));
	if (m_width > 0 && m_height > 0)
	{
		m_data.resize(m_width * m_height);
		in.read((char*)(&m_data.at(0)), m_width * m_height * sizeof(unsigned char));
	}

	mat.create(m_height, m_width, CV_8UC1);
	memcpy(mat.data, &m_data[0], m_width * m_height * sizeof(unsigned char));
}

bool load_from_bin(cv::Mat& position, cv::Mat& color, cv::Mat& flags, cv::Mat& depth, const char* bin_file)
{
	std::fstream in(bin_file, std::ios::binary | std::ios::in);
	if (in.is_open())
	{
		char OPC_MAGIC_HEAD[20] = "2ld3dsasd887dsafdsa";
		char magic_head[20];
		in.read(magic_head, 20);
		if (!strcmp(magic_head, OPC_MAGIC_HEAD))
		{
			load_cloud(position, flags, in);
			load_mat(color, in);
			load_mat(depth, in);
			in.close();
			return true;
		}
	}

	in.close();
	return false;
}