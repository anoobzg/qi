#pragma once
#include <QOpenGLFunctions>
#include "zgraphicsexport.h"

struct RenderContext
{
	QOpenGLFunctions* func;
};

class QMouseEvent;
class QWheelEvent;
class EventListener
{
public:
	virtual ~EventListener() {}

	virtual void mousePressEvent(QMouseEvent *event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent *event) = 0;
	virtual void mouseMoveEvent(QMouseEvent *event) = 0;
	virtual void wheelEvent(QWheelEvent *event) = 0;

	virtual void resize(int w, int h) = 0;
};
