#ifndef TACHE_H
#define TACHE_H

#include <QObject>
#include <QDate>

#include "item.h"


class Tache : public Item
{
    Q_OBJECT
public:
    int getPercentage();
    void setPercentage(int perc);
    Tache(Item * conteneur, QObject *parent = 0);
    Tache(QString nom, QDate date, QString description, Item * conteneur, QObject *parent = 0);

signals:
private:
    int percentage;
    
public slots:
    
};

#endif // TACHE_H
