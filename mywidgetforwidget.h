#ifndef MYWIDGETFORWIDGET_H
#define MYWIDGETFORWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QScrollArea>

#include "controleur.h"

class myWidgetForWidget : public QScrollArea
{
    Q_OBJECT

private:
    Controleur * controler;
public:
    explicit MyWidgetForWidget(Controleur * control, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);

signals:
    void add();

public slots:

};

#endif // MYWIDGETFORWIDGET_H

