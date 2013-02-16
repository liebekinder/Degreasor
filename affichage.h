#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QObject>
#include <QScrollArea>
#include <QGridLayout>
#include <QVBoxLayout>

#include "ensemble.h"
#include "item.h"
#include "tache.h"
#include "liste.h"
#include "widget.h"
#include "mywidget.h"
#include "controleur.h"

class Affichage : public QObject
{
    Q_OBJECT
public:
    explicit Affichage(QObject *parent = 0);
    myWidget * getScrollArea(Item * root_, Controleur * ctrl);
    myWidget * vue;
    QGridLayout * centralLO;
    QWidget * centralWO;
    myWidget * monWidget;
    QVBoxLayout * monWidgetL;
    void process(Item * monSet, QGridLayout *layout);
private:
    int x;
    int y;
signals:
    
public slots:
    
};

#endif // AFFICHAGE_H
