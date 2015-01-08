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
	CHECKVALID( m_pSysCenter );
	switch( pos )
	{
	case POS_SCREENCENTER:
		{
			int width = (int)m_pSysCenter->getSysProperty(Utils::SCREEN_WIDTH);
			int height = (int)m_pSysCenter->getSysProperty(Utils::SCREEN_HEIGHT);
			int left = width/2 - size().width()/2;
			int top = height/2 - size().height()/2;
			move( left+500, top );
		}
		break;
	}
}