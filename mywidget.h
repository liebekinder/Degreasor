#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QScrollArea>

#include "controleur.h"

class myWidget : public QScrollArea
{
    Q_OBJECT

private:
    Controleur * controler;
public:
    explicit myWidget(Controleur * control, QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    void deleteThis();
    
signals:
    void add();
    
public slots:
    
};

#endif // MYWIDGET_H
