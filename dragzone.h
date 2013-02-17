#ifndef DRAGZONE_H
#define DRAGZONE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class Widget;
QT_END_NAMESPACE

class DragZone : public QWidget
{
    Q_OBJECT
public:
    explicit DragZone(Widget * pere,QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *event);
private:
    Widget * parent;
signals:
    
public slots:
    
};

#endif // DRAGZONE_H
