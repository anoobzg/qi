#include "orderpointcloud.h"
#include <QColor>
#include <fstream>
#include <zlib.h>

OrderPointCloud::OrderPointCloud()
	:m_width(0),m_height(0), m_vertex_size(0)
{

}

void OrderPointCloud::Fill(int width, int height, const char* flag, const float* position, const char* color)
{
	m_width = width;
	m_height = height;
	m_vertex_size = 0;
	const unsigned char* flags = (const unsigned char*)flag;
	int total_size = m_width * m_height;
	int vertex_size = 0;
	if (m_width > 0 && m_height > 0)
	{
		for (int i = 0; i < total_size; ++i)
			if (flags[i] == 1)
				++vertex_size;

		m_flags.resize(total_size, -1);
	}

	if (vertex_size)
	{
		m_positions.resize(vertex_size * 3);
		m_colors.resize(vertex_size * 4);

		int current_index = 0;
		float* d_position = &m_positions.at(0);
		unsigned char* d_color = &m_colors.at(0);
		float* s_position = (float*)position;
		unsigned char* s_color = (unsigned char*)color;
		for (int i = 0; i < total_size; ++i)
		{
			if (*(flags + i) == 1)
			{
				m_flags.at(i) = current_index;
				float* t_position = s_position + 3 * i;
				*d_position++ = *t_position++;
				*d_position++ = *t_position++;
				*d_position++ = *t_position++;
				unsigned char c = *(s_color + i);
				*d_color++ = c; *d_color++ = c; *d_color++ = c; *d_color++ = 255;
				++current_index;
			}
		}

		m_vertex_size = vertex_size;
	}
}

OrderPointCloud::~OrderPointCloud()
{

}

int OrderPointCloud::GetWidth()
{
	return m_width;
}

int OrderPointCloud::GetHeight()
{
	return m_height;
}

int OrderPointCloud::GetSize()
{
	return m_vertex_size;
}

const std::vector<int>& OrderPointCloud::GetFlags()
{
	return m_flags;
}

const std::vector<float>& OrderPointCloud::GetPositions()
{
	return m_positions;
}

const std::vector<unsigned char>& OrderPointCloud::GetColors()
{
	return m_colors;
}

void OrderPointCloud::Save(std::fstream& out)
{
	int width = GetWidth();
	int height = GetHeight();
	int vertex_size = GetSize();
	const std::vector<int>& flags = GetFlags();
	const std::vector<float>& positions = GetPositions();
	const std::vector<unsigned char>& colors = GetColors();

	out.write((const char*)&width, sizeof(int));
	out.write((const char*)&height, sizeof(int));
	out.write((const char*)&vertex_size, sizeof(int));
	int flags_size = (int)flags.size();
	out.write((const char*)&flags_size, sizeof(int));
	if (flags_size) out.write((const char*)(&flags.at(0)), flags_size * sizeof(int));
	int position_size = (int)positions.size();
	out.write((const char*)&position_size, sizeof(int));
	if (position_size) out.write((const char*)(&positions.at(0)), position_size * sizeof(float));
	int color_size = (int)colors.size();
	out.write((const char*)&color_size, sizeof(int));
	if (color_size) out.write((const char*)(&colors.at(0)), color_size * sizeof(unsigned char));
}

void OrderPointCloud::Load(std::fstream& in)
{
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
}

void OrderPointCloud::SaveCompress(std::fstream& out)
{
	int width = GetWidth();
	int height = GetHeight();
	int vertex_size = GetSize();
	const std::vector<int>& flags = GetFlags();
	const std::vector<float>& positions = GetPositions();
	const std::vector<unsigned char>& colors = GetColors();

	int buffer_len = vertex_size * 3 * sizeof(float);
	std::vector<char> buffer(vertex_size * 3 * sizeof(float), 0);
	out.write((const char*)&width, sizeof(int));
	out.write((const char*)&height, sizeof(int));
	out.write((const char*)&vertex_size, sizeof(int));
	int flags_size = (int)flags.size();
	out.write((const char*)&flags_size, sizeof(int));
	if (flags_size)
		Compress(out, &buffer[0], buffer_len, (char*)&flags[0], flags_size * sizeof(int));
	int position_size = (int)positions.size();
	out.write((const char*)&position_size, sizeof(int));
	if (position_size)
		Compress(out, &buffer[0], buffer_len, (char*)&positions[0], position_size * sizeof(float));
	int color_size = (int)colors.size();
	out.write((const char*)&color_size, sizeof(int));
	if(color_size)
		Compress(out, &buffer[0], buffer_len, (char*)&colors[0], color_size * sizeof(unsigned char));
}

void OrderPointCloud::Compress(std::fstream& out, char* buffer, int buffer_len, char* data, int data_len)
{
	uLongf dst_len = (unsigned long)buffer_len;
	int error = compress((Bytef*)buffer, &dst_len, (Bytef*)data, (uLongf)data_len);
	assert(error == Z_OK);
	if (dst_len > 0)
	{
		out.write((const char*)&dst_len, sizeof(uLongf));
		out.write((const char*)buffer, dst_len);
	}
}
void OrderPointCloud::LoadUncompress(std::fstream& in)
{
	in.read((char*)(&m_width), sizeof(int));
	in.read((char*)(&m_height), sizeof(int));
	in.read((char*)(&m_vertex_size), sizeof(int));
	int flags_size = 0;
	in.read((char*)&flags_size, sizeof(int));
	if (flags_size)
	{
		m_flags.resize(flags_size);
		Uncompress(in, (char*)(&m_flags.at(0)), flags_size * sizeof(int));
	}

	int position_size = 0;
	in.read((char*)&position_size, sizeof(int));
	if (position_size)
	{
		m_positions.resize(position_size);
		Uncompress(in, (char*)(&m_positions.at(0)), position_size * sizeof(int));
	}
	int color_size = 0;
	in.read((char*)&color_size, sizeof(int));
	if (color_size)
	{
		m_colors.resize(color_size);
		Uncompress(in, (char*)(&m_colors.at(0)), color_size * sizeof(unsigned char));
	}
}

void OrderPointCloud::Uncompress(std::fstream& in, char* data, int data_len)
{
	uLongf compress_len;
	in.read((char*)&compress_len, sizeof(uLongf));
	if (compress_len > 0)
	{
		std::vector<char> buffer(compress_len);
		in.read((char*)&buffer[0], sizeof(char) * compress_len);
		uLongf dst_len = (uLongf)data_len;
		int error = uncompress((Bytef*)data, &dst_len, (const Bytef*)&buffer[0], (uLong)compress_len);
		assert(dst_len == data_len);
		assert(error == Z_OK);
	}
}