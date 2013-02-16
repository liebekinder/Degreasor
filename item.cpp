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
    if(t != "ensemble" && t != "liste" && t != "tache"){
        qErrnoWarning(10, "le type crée n'existe pas!");
    }
    else{
        TYPE = t;
    }
}

QString Item::getType()
{
    return TYPE;
}

QString Item::getNom()
{
    return nom_;
}

QDate Item::getDate()
{
    return date_;
}

Item::DateRelative Item::getDateR()
{
    return dateR_;
}

QString Item::getDescription()
{
    return description_;
}

void Item::setNom(QString n)
{
    nom_ = n;
}

void Item::setDate(QDate d)
{
    date_ = d;
}

void Item::setDateR(Item::DateRelative r)
{
    dateR_ = r;
}

void Item::setDescription(QString i)
{
    description_ = i;
}


Item::Item(QString nom, QDate date, QString description, QObject *parent) :
    QObject(parent)
{
    nom_ = nom;
    date_ = date;
    description_ = description;
}
