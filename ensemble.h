#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <QObject>
#include <QDate>
#include <QDebug>

#include "item.h"

class Ensemble : public Item
{
    Q_OBJECT
public:

    Ensemble(QString nom, QDate date, QString description, Item * conteneur, QObject *parent = 0);
    Ensemble(Item * conteneur, QObject *parent = 0);
    Ensemble(bool b, QObject *parent = 0);

    void ajoutItem(Item * it);
    QList<Item *> * getNotreListe();

private:
    QList<Item *> * notreListe_;

signals:
    
public slots:
    
};

#endif // ENSEMBLE_H
