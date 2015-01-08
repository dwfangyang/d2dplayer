#ifndef QTMAINWND_H
#define QTMAINWND_H

#include <QtCore/QObject>
#include <QMainWindow>
#include "inttypes.h"
#include "utils.h"

class SystemServiceCenter;
class qtMainWnd: public QMainWindow
{
	Q_OBJECT

public:
	enum WndPos
	{
		POS_SCREENCENTER,
	};
	qtMainWnd(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~qtMainWnd();

	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	void			setPos(uint32_t pos);
private:
	QPoint								mousepos;
	QPoint								windowpos;
	SystemServiceCenter*		m_pSysCenter;
};

#endif