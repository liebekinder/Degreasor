#include "ensemble.h"

Ensemble::Ensemble(QString nom, QDate date, QString description, Item *conteneur, QObject *parent) :
    Item(nom, date, description, conteneur, parent)
{
    setType("ensemble");
    notreListe_ = new QList<Item *>();
}

Ensemble::Ensemble(Item * conteneur, QObject *parent):
    Item(conteneur, parent)
{
    setType("ensemble");
    notreListe_ = new QList<Item *>();
}

Ensemble::Ensemble(bool b, QObject *parent):
    Item(b, parent)
{
    setType("ensemble");
    notreListe_ = new QList<Item *>();
}

void Ensemble::ajoutItem(Item *it)
{
    notreListe_->push_back(it);
    qDebug()<<"ajout?";
}

QList<Item *> *Ensemble::getNotreListe()
{
    return notreListe_;
}
