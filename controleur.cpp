#include "controleur.h"

Controleur::Controleur(QObject *parent) :
    QObject(parent)
{
    ensemble_ = new Ensemble("nom",QDate::currentDate(),"");
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

void Controleur::affichage(Item * monSet)
{
    //monSet = new Ensemble("Racine", new QDate::currentDate(), "La racine de nos problèmes");

    //((Ensemble)monSet).ajoutItem();
    qDebug()<<"Affichage mouhaha !";
}
