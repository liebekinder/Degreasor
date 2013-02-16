#include "controleur.h"

Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
    root_ = new Ensemble(true);
    //root_ = new Ensemble("nom", QDate::currentDate(),"bla", NULL);
    //qDebug()<< Item::TwoDaysAfter;

}

void Controleur::addEnsembleApres()
{
    qDebug()<<"ajout détecté! Ensemble avant";
}

void Controleur::addListeApres()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addTacheApres()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addTacheApresTache()
{
    qDebug()<<"[T]ajout détecté!";
}

void Controleur::addEnsemble()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addListe()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addTache()
{
    qDebug()<<"ajout détecté!";
}

Item * Controleur::getRoot()
{
    return root_;
}
