#include "controleur.h"

#include "mainwindow.h"


Controleur::Controleur(MainWindow * theControlledWindow,QObject *parent) :
    QObject(parent)
{
    root_ = new Ensemble(true);
    this->theControlledWindow = theControlledWindow;
    //root_ = new Ensemble("nom", QDate::currentDate(),"bla", NULL);
    //qDebug()<< Item::TwoDaysAfter;

}

void Controleur::addEnsembleApres()
{
    ((Ensemble *)root_)->ajoutItem(new Ensemble("Default_Ensemble",QDate::currentDate(),"",root_));
    qDebug()<<"ajout détecté! Ensemble avant";
}

void Controleur::parseAndAddAfter(Item * currentList, Item * elementPere ,Item * elementToAdd)
{
    Item * root;
    if(currentList->getType()=="ensemble") root = ((Ensemble *)currentList);
    else root = ((Liste *)currentList);


    QList<Item *>::iterator it;
    QList<Item *> * maListe = currentList->getType()=="ensemble" ? ((Ensemble *)root)->getNotreListe() :  ((Liste *)root)->getNotreListe() ;

    for(it= maListe->begin();it != maListe->end();++it)
    {

        Item * currentItem = ((Item*)*it);

        qDebug()<<"de  "+currentItem->getNom();
        if(currentItem==elementPere)
        {
            if(currentList->getType()=="ensemble") {
                elementToAdd->setParent(currentList);
                ((Ensemble *)currentList)->ajoutItem(elementToAdd);
                break;
            }
            else
            {
                elementToAdd->setParent(currentList);
                ((Liste *)currentList)->ajoutItem(elementToAdd);
                break;
            }
        }
        else
        {
            if(currentItem->getType()=="ensemble")
            {
                Controleur::parseAndAddAfter(currentItem, elementPere ,elementToAdd);
            }
            if(currentItem->getType()=="liste")
            {
                Controleur::parseAndAddAfter(currentItem, elementPere ,elementToAdd);
            }
        }

    }
}

void Controleur::addListeApres()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addTacheApres()
{
    qDebug()<<"ajout détecté!";

}

void Controleur::addTacheALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
}

void Controleur::addListeALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
}

void Controleur::addEnsembleALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
}

void Controleur::addTacheApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
}

void Controleur::addListeApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
}

void Controleur::addEnsembleApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Yeah",QDate::currentDate(),"Yeah bis", NULL); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh();
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

