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
    /*monSet = new Ensemble("Racine", QDate::currentDate(), "La racine de nos problèmes");
    Tache * num1 = new Tache("Tache 1", QDate::currentDate(), "Execution du chien");
    Liste * num2 = new Liste("Liste 2", QDate::currentDate(), "Quelques exécutions");
    Tache * num3 = new Tache("Tache 3", QDate::currentDate(), "Execution du lapin");
    Tache * num4 = new Tache("Tache 4", QDate::currentDate(), "Execution du chat");
    Ensemble * root = ((Ensemble *)monSet);
    root->ajoutItem(num1);
        num2->ajoutItem(num3);
        num2->ajoutItem(num4);
    root->ajoutItem(num2);*/

    qDebug()<<"Affichage mouhaha !";
}
