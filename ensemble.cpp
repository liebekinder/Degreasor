#include "ensemble.h"

Ensemble::Ensemble(QString nom, QDate date, QString description, QObject *parent) :
    Item(nom, date, description, parent)
{
    TYPE = "ensemble";
    notreListe_ = new QList<Item *>();
}

Ensemble::Ensemble(QObject *parent):
    Item(parent)
{
    TYPE = "ensemble";
}

void Ensemble::ajoutItem(Item *it)
{
    notreListe_->push_back(it);
}
