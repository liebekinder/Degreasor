#ifndef LISTE_H
#define LISTE_H

#include <QObject>
#include <QDate>

#include "item.h"

class Liste : public Item
{
    Q_OBJECT
public:

    Liste(QString nom, QDate date, QString description, Item * conteneur, QObject *parent = 0);
    Liste(Item * conteneur, QObject *parent = 0);

    void ajoutItem(Item * it);
    QList<Item *> * getNotreListe();

    void ajoutItem(Item *it, int pos);
    void ajoutItem(Item *it, Item * db);
private:
    QList<Item *> * notreListe_;

signals:

public slots:

};

#endif // LISTE_H
