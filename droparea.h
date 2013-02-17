#ifndef DROPAREA_H
#define DROPAREA_H

#include <QWidget>
#include <QDebug>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class DropArea : public QWidget
{
    Q_OBJECT
public:
    explicit DropArea(QWidget *parent = 0);
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    
public slots:
    
};

#endif // DROPAREA_H
