#include "qtMainWnd.h"
#include <QtGui/QWidget>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsItem>

qtMainWnd::qtMainWnd(QWidget* parent,Qt::WindowFlags flags) : QMainWindow(parent,flags)
{
	QGraphicsView* view = new QGraphicsView(this);
	QGraphicsScene* scene = new QGraphicsScene(this);
	QGraphicsTextItem* item = new QGraphicsTextItem(NULL,scene);
	item->setParent(scene);
	scene->addItem(item);
	item->setPlainText("great");
	view->setScene(scene);
}

qtMainWnd::~qtMainWnd()
{

}