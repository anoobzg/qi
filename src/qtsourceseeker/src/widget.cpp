#include <QApplication>
#include <QWidget>
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QWidget w;
	w.resize(400, 400);
	w.showNormal();

	QWidget w2;
	w2.move(0, 0);
	w2.resize(100, 100);
	w2.showNormal();
	int result = app.exec();
	return result;
} 