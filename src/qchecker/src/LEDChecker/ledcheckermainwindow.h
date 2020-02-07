#pragma once
#include <QMainWindow>

namespace Ui 
{
	class ledchecker;
} // namespace Ui

class ILEDChecker;
struct RenderContext;
class LEDCheckerMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	LEDCheckerMainWindow();
	~LEDCheckerMainWindow();

protected slots:
	void on_openaction_triggered();
	void on_saveaction_triggered();
	void on_openglwidget_draw(RenderContext& context);
private:
	Ui::ledchecker* m_ui;

	ILEDChecker* m_checker;
};