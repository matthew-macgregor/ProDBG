#include "CustomView.h"
#include <PDUI.h>
#include <QPainter>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace prodbg
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CustomView::CustomView(QWidget* parent, void* userData, PDCustomDrawCallback callback) : 
	QWidget(parent),
	m_userData(userData),
	m_callback(callback)
{
	printf("created customViwe\n");
	resize(200, 200);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int fill_rect(void* privateData, int x, int y, int w, int h, unsigned int color)
{
	QPainter* painter = (QPainter*)privateData;
	QRect rect(QPoint(x, y), QPoint(w, h));
	painter->fillRect(rect, color);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void initPainter(PDUIPainter* pdPainter, QPainter* qPainter)
{
	pdPainter->privateData = (void*)qPainter;
	pdPainter->fill_rect = fill_rect;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CustomView::paintEvent(QPaintEvent* event)
{
	PDUIPainter pdPainter;
	QPainter qPainter(this); 

	pdPainter.privateData = &qPainter;
	pdPainter.fill_rect = fill_rect;

	m_callback(m_userData, &pdPainter);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
