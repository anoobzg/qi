#pragma once
#include <QMainWindow>

namespace Ui 
{
	class ledchecker;
} // namespace Ui

class LEDCheckerMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	LEDCheckerMainWindow();
	~LEDCheckerMainWindow();

protected slots:
	void on_openaction_triggered();
	void on_saveaction_triggered();
private:
	Ui::ledchecker* m_ui;
};