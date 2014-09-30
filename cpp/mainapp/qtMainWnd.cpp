#include "qtMainWnd.h"
#include "SystemServiceCenter.h"
#include <QtGui/QWidget>
#include <QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsItem>

qtMainWnd::qtMainWnd(QWidget* parent,Qt::WindowFlags flags) : QMainWindow(parent,flags),m_pSysCenter(NULL)
{
	QGraphicsView* view = new QGraphicsView(this);
	QGraphicsScene* scene = new QGraphicsScene(this);
	QGraphicsTextItem* item = new QGraphicsTextItem(NULL,scene);
	item->setParent(scene);
	scene->addItem(item);
	item->setPlainText("great");
	view->setScene(scene);

	m_pSysCenter = SystemServiceCenter::getInstance();
}

qtMainWnd::~qtMainWnd()
{

}

void qtMainWnd::mousePressEvent(QMouseEvent *event)
{
	mousepos = event->globalPos();
	windowpos = pos();
}

void qtMainWnd::mouseMoveEvent(QMouseEvent *event)
{
	move( windowpos + event->globalPos() - mousepos);
}

void qtMainWnd::setPos(uint32_t pos)
{
	switch( pos )
	{
	case POS_SCREENCENTER:
		{
			if ( m_pSysCenter )
			{
				int width = (int)m_pSysCenter->getSysProperty(SCREEN_WIDTH);
				int height = (int)m_pSysCenter->getSysProperty(SCREEN_HEIGHT);
				int left = width/2 - size().width()/2;
				int top = height/2 - size().height()/2;
				move( left, top );
			}
		}
		break;
	}
}