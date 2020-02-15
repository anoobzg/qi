#pragma once
#include <QString>
#include <QVector>
#include <QListWidget>

#include "Logging.h"

namespace SyntopiaCore
{
	namespace Logging
	{	
		class ListWidgetLogger : public QListWidget, public Logger
		{
		public:
			ListWidgetLogger(QWidget* parent);
			virtual ~ListWidgetLogger();

			/// This method all loggers must implement
			void log(QString message, LogLevel priority);
		private:
			QWidget* parent;
		};
		
	}
}

