#ifndef ENTETE_H
#define ENTETE_H

#include <QWidget>
#include <QtGui>
#include <QtCore/qmath.h>
#include <QApplication>


class Widget;

class entete : public QWidget
{
    Q_OBJECT

public:
    explicit entete(int numEntete,int typeV,Widget * papa,QWidget *parent = 0);
    void setPercent(int perc);
    void setType(int typeV);
    void setEntete(int numEntete);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    int percent;
    int numeroEntete;
    int type;
    Widget * papa;
    
signals:
    
public slots:
    
};

#endif // ENTETE_H
