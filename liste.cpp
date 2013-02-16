#include "liste.h"

Liste::Liste(QString nom, QDate date, QString description, Item * conteneur, QObject *parent) :
    Item(nom, date, description, conteneur, parent)
{
    setType("liste");
    notreListe_ = new QList<Item *>();
}

Liste::Liste(Item * conteneur, QObject *parent):
    Item(conteneur, parent)
{
    setType("liste");
    notreListe_ = new QList<Item *>();
}

void Liste::ajoutItem(Item *it)
{
    notreListe_->push_back(it);
}

QList<Item *> * Liste::getNotreListe()
{
    return notreListe_;
}
