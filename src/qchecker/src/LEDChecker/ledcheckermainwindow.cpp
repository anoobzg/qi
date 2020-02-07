#include "ledcheckermainwindow.h"
#include "ui_ledchecker.h"

#include <QFileDialog>
#include "ledcheckerinstance.h"
#include "ledalgrithminterface.h"

LEDCheckerMainWindow::LEDCheckerMainWindow()
	:m_ui(nullptr), m_checker(nullptr)
{
	m_ui = new Ui::ledchecker();
	m_ui->setupUi(this);

	m_checker = GetLEDCheckerInstance();
}

LEDCheckerMainWindow::~LEDCheckerMainWindow()
{
	delete m_ui;
	m_checker = nullptr;
}

void LEDCheckerMainWindow::on_openaction_triggered()
{
	QString file_name = QFileDialog::getOpenFileName(this);
	if(m_checker->LoadFromFile(file_name.toStdString().c_str()))
	{

	}
}

void LEDCheckerMainWindow::on_saveaction_triggered()
{
	QString file_name = QFileDialog::getSaveFileName(this);
	m_checker->SaveToFile(file_name.toStdString().c_str());
}

void LEDCheckerMainWindow::on_openglwidget_draw(RenderContext& context)
{

}