#include "MiscDataCenter.h"
#include <QStringList>

static QStringList s_search_path;
static QString s_misc_directory;
static QString s_example_directory;
void MiscDataCenter::AppendSearchPath(const QString& path)
{
	s_search_path.append(path);
}

void MiscDataCenter::ClearAllSearchPath()
{
	s_search_path.clear();
}

void MiscDataCenter::SetMiscDirectory(const QString& directory)
{
	s_misc_directory = directory;
}

QString MiscDataCenter::GetMiscDirectory()
{
	return s_misc_directory;
}

void MiscDataCenter::SetExampleDirectory(const QString& directory)
{
	s_example_directory = directory;
}

QString MiscDataCenter::GetExampleDirectory()
{
	return s_example_directory;
}