#include <QApplication>
#include <QWidget>
#include <QMainwindow>
#include <QMenuBar>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	QMainWindow main_window;
	main_window.resize(500, 500);
	main_window.showNormal();

	QMenuBar* menu_bar = main_window.menuBar();
	QMenu* menu = menu_bar->addMenu("FILE");
	int result = app.exec();
	return result;
} 