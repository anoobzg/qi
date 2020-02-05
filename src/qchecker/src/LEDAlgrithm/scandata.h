#pragma once
#include <QScopedPointer>
#include "orderpointcloud.h"
#include "imagedata.h"

class ScanData
{
public:
	ScanData();
	~ScanData();

	OrderPointCloud* GetCloud();
	void SetCloud(OrderPointCloud* cloud);
	ImageData* GetRawImage();
	void SetRawImage(ImageData* image);
	ImageData* GetHeightImage();
	void SetHeightImage(ImageData* image);

	void Save(const std::string& file);
	bool Load(const std::string& file);
protected:
	bool EndWidth(const std::string& file, const std::string& extension);
	void SaveBinary(std::fstream& out);
	void SaveCompress(std::fstream& out);
private:
	QScopedPointer<OrderPointCloud> m_cloud;
	QScopedPointer<ImageData> m_raw_image;
	QScopedPointer<ImageData> m_height_image;
};