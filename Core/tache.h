#ifndef TACHE_H
#define TACHE_H

#include <QObject>
#include <QDate>

#include "item.h"


class Tache : public Item
{
    Q_OBJECT
public:
    Tache(Item * conteneur, QObject *parent = 0);
    Tache(QString nom, QDate date, QString description, Item * conteneur, QObject *parent = 0);

signals:
private:

    
public slots:
    
};

#endif // TACHE_H
