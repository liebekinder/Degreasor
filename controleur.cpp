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

/*void Controleur::parseAndAddAfter(Item * currentList, Item * elementPere ,Item * elementToAdd)
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
}*/

void Controleur::addEnsembleApres()
{
    Item * yeah = new Ensemble("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    qDebug()<<"ajout détecté! Ensemble avant";
    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApres()
{
    Item * yeah = new Liste("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    qDebug()<<"ajout détecté!";
    theControlledWindow->refresh(yeah);
}

void Controleur::addTacheApres()
{
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    qDebug()<<"ajout détecté!";
    theControlledWindow->refresh(yeah);

}

void Controleur::addTacheALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh(yeah);
}

void Controleur::addListeALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);;
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsembleALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";

    theControlledWindow->refresh(yeah);
}

void Controleur::addTacheApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"", test); //on set le parent quand on le connais
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

    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"", test); //on set le parent quand on le connais
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

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsembleApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"", test); //on set le parent quand on le connais
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

    theControlledWindow->refresh(yeah);
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

void Controleur::callRefreshWithoutMoveScreen()
{
    theControlledWindow->callRefreshWithoutMoveScreen();
}

