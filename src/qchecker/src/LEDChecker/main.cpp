#include <iostream>
#include <QApplication>
#include "ledcheckermainwindow.h"
#include "ledcheckerinstance.h"

int main(int argc, char* argv[])
{
	InitializeLEDCheckerInstance();

	QApplication app(argc, argv);

	LEDCheckerMainWindow window;
	window.showMaximized();
	int exit = app.exec();

	ReleaseLEDCheckerInstance();
	return exit;
}