#pragma once
#include <QVector3D>
#include <vector>
#include <fstream>

class OrderPointCloud
{
public:
	OrderPointCloud();
	~OrderPointCloud();
	
	void Fill(int width, int height, const char* flag, const float* position, const char* color);

	int GetWidth();
	int GetHeight();
	int GetSize();
	const std::vector<int>& GetFlags();
	const std::vector<float>& GetPositions();
	const std::vector<unsigned char>& GetColors();

	void Save(std::fstream& out);
	void Load(std::fstream& in);
	void SaveCompress(std::fstream& out);
	void LoadUncompress(std::fstream& in);
private:
	void Compress(std::fstream& out, char* buffer, int buffer_len, char* data, int data_len);
	void Uncompress(std::fstream& in, char* data, int data_len);
protected:
	int m_width;
	int m_height;
	int m_vertex_size;
	std::vector<int> m_flags;
	std::vector<float> m_positions;
	std::vector<unsigned char> m_colors;
};