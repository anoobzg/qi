#include "imagedata.h"
#include <zlib.h>
#include <assert.h>

ImageData::ImageData()
	:m_width(0), m_height(0)
{

}

ImageData::~ImageData()
{

}

void ImageData::Fill(int width, int height, unsigned char* data)
{
	m_width = width;
	m_height = height;
	if (m_width && m_height)
	{
		m_data.resize(m_width * m_height, 0);
		if(data) memcpy(&m_data[0], data, m_width * m_height * sizeof(unsigned char));
	}
}

int ImageData::Width()
{
	return m_width;
}

int ImageData::Height()
{
	return m_height;
}

unsigned char* ImageData::Data()
{
	return m_data.size() > 0 ? &m_data[0] : 0;
}

void ImageData::Load(std::fstream& in)
{
	in.read((char*)(&m_width), sizeof(int));
	in.read((char*)(&m_height), sizeof(int));
	if (m_width > 0 && m_height > 0)
	{
		m_data.resize(m_width * m_height);
		in.read((char*)(&m_data.at(0)), m_width * m_height * sizeof(unsigned char));
	}
}

void ImageData::Save(std::fstream& out)
{
	out.write((const char*)&m_width, sizeof(int));
	out.write((const char*)&m_height, sizeof(int));

	if (m_width > 0 && m_height > 0) out.write((const char*)(&m_data.at(0)), m_width * m_height * sizeof(unsigned char));
}

void ImageData::LoadUncompress(std::fstream& in)
{
	in.read((char*)(&m_width), sizeof(int));
	in.read((char*)(&m_height), sizeof(int));
	if (m_width > 0 && m_height > 0)
	{
		m_data.resize(m_width * m_height);
		Uncompress(in, (char*)&m_data.at(0), m_width * m_height * sizeof(unsigned char));
	}
}

void ImageData::SaveCompress(std::fstream& out)
{
	out.write((const char*)&m_width, sizeof(int));
	out.write((const char*)&m_height, sizeof(int));

	if (m_width > 0 && m_height > 0)
	{
		int buffer_len = m_width * m_height * sizeof(unsigned char);
		std::vector<char> buffer(buffer_len, 0);
		Compress(out, &buffer[0], buffer_len, (char*)&m_data[0], buffer_len);
	}
}

void ImageData::Compress(std::fstream& out, char* buffer, int buffer_len, char* data, int data_len)
{
	uLongf dst_len = (unsigned long)buffer_len;
	int error = compress((Bytef*)buffer, &dst_len, (Bytef*)data, (uLongf)data_len);
	assert(error == Z_OK);
	if ((dst_len > 0) && (error == Z_OK))
	{
		out.write((const char*)&dst_len, sizeof(uLongf));
		out.write((const char*)buffer, dst_len);
	}
}

void ImageData::Uncompress(std::fstream& in, char* data, int data_len)
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