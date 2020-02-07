#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "zgrenderheader.h"

class ZG_API ZOpenGLWidget : public QOpenGLWidget
	, public QOpenGLFunctions
{
	Q_OBJECT
public:
	ZOpenGLWidget(QWidget* parent);
	~ZOpenGLWidget();

	void EnableRender(bool enable, int time = 33);
	void SetEventListener(EventListener* listener);
protected:
	void initializeGL() override; 
	void resizeGL(int w, int h) override;
	void paintGL() override;

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
#if QT_CONFIG(wheelevent)
	virtual void wheelEvent(QWheelEvent *event);
#endif

signals:
	void draw(RenderContext& context);
private:
	QTimer* m_timer;
	EventListener* m_listener;

	RenderContext m_context;
};