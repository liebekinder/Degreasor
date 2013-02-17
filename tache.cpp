#include "tache.h"

Tache::Tache(Item * conteneur, QObject *parent) :
    Item(conteneur, parent)
{
    percentage = 0;
    setType("tache");
}

Tache::Tache(QString nom, QDate date, QString description, Item * conteneur, QObject *parent) :
    Item(nom, date, description, conteneur, parent)
{
    percentage = 0;
    setType("tache");
}

int Tache::getPercentage()
{
    return percentage;
}

void Tache::setPercentage(int perc)
{
    this->percentage = perc;
}
