#include "item.h"

Item::Item(QObject *parent) :
    QObject(parent)
{
    nom_ = "Mon nouvel item";
    date_ = QDate::currentDate();
}


Item::Item(QString nom, QDate date, QString description, QObject *parent) :
    QObject(parent)
{
    nom_ = nom;
    date_ = date;
    description_ = description;
}
