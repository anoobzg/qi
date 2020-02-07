#include "zgopenglwidget.h"
#include <QTimer>

ZOpenGLWidget::ZOpenGLWidget(QWidget* parent)
	:QOpenGLWidget(parent), m_listener(NULL)
{
	m_timer = new QTimer(this);
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	
	EnableRender(true);

	m_context.func = this;
}

ZOpenGLWidget::~ZOpenGLWidget()
{
	EnableRender(false);
}

void ZOpenGLWidget::EnableRender(bool enable, int time)
{
	m_timer->stop();
	if (enable) m_timer->start(time);
}

void ZOpenGLWidget::SetEventListener(EventListener* listener)
{
	m_listener = listener;
}

void ZOpenGLWidget::initializeGL()
{
	initializeOpenGLFunctions();
}

void ZOpenGLWidget::resizeGL(int w, int h)
{
	if (m_listener) m_listener->resize(w, h);
}

void ZOpenGLWidget::paintGL()
{
	emit draw(m_context);
}

void ZOpenGLWidget::mousePressEvent(QMouseEvent *event)
{
	if (m_listener) m_listener->mousePressEvent(event);
}

void ZOpenGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (m_listener) m_listener->mouseReleaseEvent(event);
}

void ZOpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	if (m_listener) m_listener->mouseMoveEvent(event);
}

#if QT_CONFIG(wheelevent)
void ZOpenGLWidget::wheelEvent(QWheelEvent *event)
{
	if (m_listener) m_listener->wheelEvent(event);
}
#endif