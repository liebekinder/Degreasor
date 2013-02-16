#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPaintEvent>
#include <QtGui>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>

#include "controleur.h"
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
    void mousePressEvent(QMouseEvent *event);
    explicit Widget(Controleur *control, QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Controleur * controler;
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
