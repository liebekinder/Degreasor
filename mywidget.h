#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "controleur.h"

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>

class myWidget : public QWidget
{
    Q_OBJECT

private:
    Controleur * controler;
public:
    explicit myWidget(Controleur * control, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
    
signals:
    void add();
    
public slots:
    
};

#endif // MYWIDGET_H
