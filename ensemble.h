#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <QObject>
#include <QDate>

#include "item.h"

class Ensemble : public Item
{
    Q_OBJECT
public:

    Ensemble(QString nom, QDate date, QString description, QObject *parent = 0);
    Ensemble(QObject *parent = 0);

    void ajoutItem(Item * it);
    QList<Item *> * getNotreListe();

private:
    QList<Item *> * notreListe_;

signals:
    
public slots:
    
};

#endif // ENSEMBLE_H
