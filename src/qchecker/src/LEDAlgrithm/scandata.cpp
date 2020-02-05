#include "scandata.h"
#include <zlib.h>

char OPC_MAGIC_HEAD[20] = "2ld3dsasd887dsafdsa";
char OPC_MAGIC_HEADZ[20] = "2ld3dsasdzz7dsafdsa";
ScanData::ScanData()
{
	m_cloud.reset(new OrderPointCloud());
	m_raw_image.reset(new ImageData());
	m_height_image.reset(new ImageData());
}

ScanData::~ScanData()
{

}

OrderPointCloud* ScanData::GetCloud()
{
	return m_cloud.get();
}

void ScanData::SetCloud(OrderPointCloud* cloud)
{
	m_cloud.reset(cloud);
}

ImageData* ScanData::GetRawImage()
{
	return m_raw_image.get();
}

void ScanData::SetRawImage(ImageData* image)
{
	m_raw_image.reset(image);
}

ImageData* ScanData::GetHeightImage()
{
	return m_height_image.get();
}

void ScanData::SetHeightImage(ImageData* image)
{
	m_height_image.reset(image);
}

void ScanData::Save(const std::string& file)
{
	std::fstream out(file.c_str(), std::ios::binary | std::ios::out);
	if (out.is_open())
	{
		if (EndWidth(file, ".z"))
			SaveCompress(out);
		else
			SaveBinary(out);
	}
	out.close();
}

void ScanData::SaveBinary(std::fstream& out)
{
	out.write(OPC_MAGIC_HEAD, 20);
	m_cloud->Save(out);
	m_raw_image->Save(out);
	m_height_image->Save(out);
}

void ScanData::SaveCompress(std::fstream& out)
{
	out.write(OPC_MAGIC_HEADZ, 20);
	m_cloud->SaveCompress(out);
	m_raw_image->SaveCompress(out);
	m_height_image->SaveCompress(out);
}

bool ScanData::Load(const std::string& file)
{
	std::fstream in(file.c_str(), std::ios::binary | std::ios::in);
	if (in.is_open())
	{
		char magic_head[20];
		in.read(magic_head, 20);
		if (!strcmp(magic_head, OPC_MAGIC_HEAD))
		{
			m_cloud->Load(in);
			m_raw_image->Load(in);
			m_height_image->Load(in);
			in.close();
			return true;
		}
		else if (!strcmp(magic_head, OPC_MAGIC_HEADZ))
		{
			m_cloud->LoadUncompress(in);
			m_raw_image->LoadUncompress(in);
			m_height_image->LoadUncompress(in);
			in.close();
			return true;
		}
	}

	in.close();
	return false;
}

bool ScanData::EndWidth(const std::string& file, const std::string& extension)
{
	std::string::const_iterator pos = std::find(file.begin(), file.end(), '.');
	if (pos != file.end())
		return strcmp((const char*)(&*pos), extension.c_str()) == 0;
	return false;
}