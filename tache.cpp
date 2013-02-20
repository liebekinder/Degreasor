#include "tache.h"

Tache::Tache(Item * conteneur, QObject *parent) :
    Item(conteneur, parent)
{
    setType("tache");
}

Tache::Tache(QString nom, QDate date, QString description, Item * conteneur, QObject *parent) :
    Item(nom, date, description, conteneur, parent)
{
    setType("tache");
}

