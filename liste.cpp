#include "liste.h"

Liste::Liste(QString nom, QDate date, QString description, QObject *parent) :
    Item(nom, date, description, parent)
{
    TYPE = "liste";
    notreListe_ = new QList<Item *>();
}

Liste::Liste(QObject *parent):
    Item(parent)
{
    TYPE = "liste";
}

void Liste::ajoutItem(Item *it)
{
    notreListe_->push_back(it);
}
