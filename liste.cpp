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

void Liste::ajoutItem(Item *it, int pos)
{
    notreListe_->insert(pos, it);

}

void Liste::ajoutItem(Item *it, Item *db)
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

QList<Item *> * Liste::getNotreListe()
{
    return notreListe_;
}
