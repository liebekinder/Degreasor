#include "item.h"

//construction
Item::Item(Item *conteneur, QObject *parent) :
    QObject(parent)
{
    nom_ = "Mon nouvel item";
    date_ = QDate::currentDate();
    setParent(conteneur);
}

Item::Item(bool root, QObject *parent) :
    QObject(parent)
{
    //root = true; //enlever le warning
    nom_ = "Root";
    date_ = QDate::currentDate();
}

Item::Item(QString nom, QDate date, QString description, Item *conteneur, QObject *parent) :
    QObject(parent)
{
    visible = true;
    nom_ = nom;
    date_ = date;
    description_ = description;
    setParent(conteneur);
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

void Item::setVisible(bool b)
{
    visible=b;
}

bool Item::getVisible()
{
    return visible;
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

QWidget *Item::getVue()
{
    return vue_;
}

Item *Item::getParent()
{
    return parent_;
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

void Item::setVue(QWidget *v)
{
    vue_ = v;
}

void Item::setParent(Item *p)
{
    parent_ = p;
}
