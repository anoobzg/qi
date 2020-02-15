#include "ListWidgetLogger.h"

namespace SyntopiaCore
{
	namespace Logging
	{
		ListWidgetLogger::ListWidgetLogger(QWidget* parent) : parent(parent)
		{ 	
		}

		ListWidgetLogger::~ListWidgetLogger()
		{ 
		}

		void ListWidgetLogger::log(QString message, LogLevel priority)
		{
			QListWidgetItem* item = new QListWidgetItem(message, this);

			// Levels: NoneLevel, DebugLevel, TimingLevel, InfoLevel, WarningLevel, CriticalLevel, AllLevel
			if ( priority == InfoLevel )
			{
				item->setBackgroundColor(QColor(255,255,255));
			} else if ( priority == WarningLevel )
			{
				//parent->show();
				item->setBackgroundColor(QColor(255,243,73));
			} else if ( priority == CriticalLevel )
			{
				//parent->show();
				item->setBackgroundColor(QColor(255,2,0));
			} else if ( priority == TimingLevel )
			{
				//parent->show();
				item->setBackgroundColor(QColor(25,255,0));
			} else
			{
				item->setBackgroundColor(QColor(220,220,220));
			}

			scrollToItem(item); 
		}

	}
}
