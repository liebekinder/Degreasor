#include "item.h"

Item::Item(QObject *parent) :
    QObject(parent)
{
    nom_ = "Mon nouvel item";
    date_ = QDate::currentDate();
}

void Item::setType(QString t)
{
    //verification des types
    if(t != "ensemble" || t != "liste" || t != "tache"){
        qErrnoWarning(10, "le type crée n'existe pas!");
    }
    else{
        TYPE = t;
    }
}


Item::Item(QString nom, QDate date, QString description, QObject *parent) :
    QObject(parent)
{
    nom_ = nom;
    date_ = date;
    description_ = description;
}
