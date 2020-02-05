#include "ledcheckermainwindow.h"
#include "ui_ledchecker.h"

#include <QFileDialog>
LEDCheckerMainWindow::LEDCheckerMainWindow()
	:m_ui(NULL)
{
	m_ui = new Ui::ledchecker();
	m_ui->setupUi(this);


}

LEDCheckerMainWindow::~LEDCheckerMainWindow()
{
	delete m_ui;
}

void LEDCheckerMainWindow::on_openaction_triggered()
{
	QString file_name = QFileDialog::getOpenFileName(this);
	if (!file_name.isEmpty())
	{

	}
}

void LEDCheckerMainWindow::on_saveaction_triggered()
{
	QString file_name = QFileDialog::getSaveFileName(this);
	if (!file_name.isEmpty())
	{

	}
}