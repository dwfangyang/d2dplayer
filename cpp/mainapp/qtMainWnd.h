#ifndef QTMAINWND_H
#define QTMAINWND_H

#include <QtCore/QObject>
#include <QMainWindow>
#include "windows.h"

class qtMainWnd: public QMainWindow
{
	Q_OBJECT

public:
	qtMainWnd(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~qtMainWnd();
};

#endif