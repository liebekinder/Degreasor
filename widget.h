#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPaintEvent>
#include <QtGui>
#include "entete.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    enum Type
        {
            ELEMENT = 0,
            LIST = 1
        };
    void setPercent(int i);
    void setEntete(int i);
    void setTitre(QString title);
    void setDate(QDate dateText);
    void setType(Type typeV);
    void setDescription(QString descriptionText);
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void Widget::paintEvent(QPaintEvent *event);
private:
    QHBoxLayout * centralLayout;
    QVBoxLayout * rightLayout;
    QHBoxLayout * subRightLayout;

    entete * chiffre;
    QLabel * titre;
    QLabel * date;
    QLabel * description;
    QFrame * lineV;
    QFrame * lineH;
    QFrame * lineH2;
    Type type;
};

#endif // WIDGET_H
