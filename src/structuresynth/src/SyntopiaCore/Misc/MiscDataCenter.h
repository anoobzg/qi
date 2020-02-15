#pragma once
#include <QString>

class MiscDataCenter
{
public:
	static void AppendSearchPath(const QString& path);
	static void ClearAllSearchPath();

	static void SetMiscDirectory(const QString& directory);
	static QString GetMiscDirectory();

	static void SetExampleDirectory(const QString& directory);
	static QString GetExampleDirectory();
};

#define MISCDIR MiscDataCenter::GetMiscDirectory()
#define EXAMPLEDIR MiscDataCenter::GetExampleDirectory()
#define TEMPLATEDIR MiscDataCenter::GetMiscDirectory()