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
#include "item.h"


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
    void mouseDoubleClickEvent(QMouseEvent *event);
    explicit Widget(Controleur *control, Item * caller, QWidget *parent = 0);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *event);
public slots:
    void addTacheApresTache();
    void addListeApresTache();
    void addEnsembleApresTache();
    void addTacheALaSuiteDeTache();
    void addListeALaSuiteDeTache();
    void addEnsembleALaSuiteDeTache();
signals:
    void addTacheApresTacheSignal(Item *);
    void addListeApresTacheSignal(Item *);
    void addEnsembleApresTacheSignal(Item *);
    void addTacheALaSuiteDeTacheSignal(Item *);
    void addListeALaSuiteDeTacheSignal(Item *);
    void addEnsembleALaSuiteDeTacheSignal(Item *);
private:
    int currentPercent;
    Item * imageOf;
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
