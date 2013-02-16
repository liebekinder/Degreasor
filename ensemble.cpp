#include "ensemble.h"

Ensemble::Ensemble(QString nom, QDate date, QString description, QObject *parent) :
    Item(nom, date, description, parent)
{
    setType("ensemble");
    notreListe_ = new QList<Item *>();
}

Ensemble::Ensemble(QObject *parent):
    Item(parent)
{
    setType("ensemble");
}

void Ensemble::ajoutItem(Item *it)
{
    notreListe_->push_back(it);
}
