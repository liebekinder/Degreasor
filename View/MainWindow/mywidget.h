#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include <QSignalMapper>

#include "controleur.h"

class myWidget : public QScrollArea
{
    Q_OBJECT

private:
    QSignalMapper * mapper;
    QSignalMapper * mapper3;
    Controleur * controler;
public:
    explicit myWidget(Controleur * control, QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void toutReduire(Item * itemC);
public slots:
    void deleteThis();
    void templateTest(int);
    void templateTest3(int i);
    
signals:
    void add();
    
public slots:
    
};

#endif // MYWIDGET_H
