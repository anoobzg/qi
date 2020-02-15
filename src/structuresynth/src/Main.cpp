#include <QApplication>
#include <QDir>
#include <QSplashScreen>
#include <QBitmap>

#include "SyntopiaCore/Misc/MiscDataCenter.h"
#include "StructureSynth/GUI/MainWindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(StructureSynth);
	MiscDataCenter::SetMiscDirectory("C:\\QI\\src\\structuresynth\\src\\Misc\\");
	MiscDataCenter::SetExampleDirectory("C:\\QI\\src\\structuresynth\\src\\Examples\\");

    QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("Syntopia Software");
    QCoreApplication::setApplicationName("Structure Synth");

	QPixmap pixmap(QDir(MISCDIR).absoluteFilePath("splash.png"));
	QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
	splash.setMask(pixmap.mask());
	splash.show();
	qApp->processEvents();

	// We will parse for filenames.
	// On Windows 'argv*' is not of much use, since it fails for Unicode paths.
	// We will fetch the unicode strings...
	QStringList args;
	for (int i = 0; i < argc; ++i)
	{
		args.append(QString::fromUtf8(argv[i]));
	}

	using namespace StructureSynth::GUI;
	MainWindow* main_window = nullptr;
	if (args.size() <= 1)
	{
		main_window = new StructureSynth::GUI::MainWindow();
	}
	else
	{
		// We ignore more then one argument
		main_window = new StructureSynth::GUI::MainWindow(args[1]);
	}

	if(main_window) main_window->show();
	
	return app.exec();
}

