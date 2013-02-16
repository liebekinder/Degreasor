#include "tache.h"

Tache::Tache(QObject *parent) :
    Item(parent)
{
    setType("tache");
}

Tache::Tache(QString nom, QDate date, QString description, QObject *parent) :
    Item(nom, date, description, parent)
{
    setType("tache");
}
