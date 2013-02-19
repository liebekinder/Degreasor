#ifndef DROPAREA_H
#define DROPAREA_H

#include <QWidget>
#include <QDebug>
#include <QListWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

class DropArea : public QWidget
{
    Q_OBJECT
public:
    //explicit DropArea(QListWidget * listeGeree, QWidget *parent = 0);
    explicit DropArea(QWidget *parent = 0);
private:
    //QListWidget * listeGeree;
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

signals:
    void dropICI(QString s);
    
public slots:
    
};

#endif // DROPAREA_H
