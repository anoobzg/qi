#pragma once
#include <vector>
#include <fstream>

class ImageData
{
public:
	ImageData();
	~ImageData();

	int Width();
	int Height();
	unsigned char* Data();
	void Fill(int width, int height, unsigned char* data = 0);

	void Load(std::fstream& in);
	void Save(std::fstream& out);
	void LoadUncompress(std::fstream& in);
	void SaveCompress(std::fstream& out);
private:
	void Compress(std::fstream& out, char* buffer, int buffer_len, char* data, int data_len);
	void Uncompress(std::fstream& in, char* data, int data_len);
protected:
	int m_width;
	int m_height;
	std::vector<unsigned char> m_data;
};