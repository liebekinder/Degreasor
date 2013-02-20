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

void Ensemble::ajoutItem(Item *it, int pos)
{
    notreListe_->insert(pos,it);
    qDebug()<<"ajout?";
}

void Ensemble::ajoutItem(Item *it, Item *db)
{
//on cherche db et on ajoute it après
    QString iddb = db->getUID().toString();
    int i = 0;
    bool trouve = false;
    while(!trouve && i<notreListe_->size()){
        if(notreListe_->at(i)->getUID() == iddb)
        {
            trouve = true;
            notreListe_->insert(i,it);
        }
        ++i;
    }

}

QList<Item *> *Ensemble::getNotreListe()
{
    return notreListe_;
}
