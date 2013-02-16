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

void Controleur::affichage(Item * monSet, QGridLayout * layout)
{
    //monSet = new Ensemble("Racine", QDate::currentDate(), "La racine de nos problèmes");

    Item * root;
    if(monSet->getType()=="ensemble") root = ((Ensemble *)monSet);
    else root = ((Liste *)monSet);


    QList<Item *>::iterator it;
    QList<Item *> * maListe = monSet->getType()=="ensemble" ? ((Ensemble *)root)->getNotreListe() :  ((Liste *)root)->getNotreListe() ;

    int counter = 1;
    for(it= maListe->begin();it != maListe->end();++it)
    {
        x++;
        Item * currentItem = ((Item*)*it);

        Widget * tempW = new Widget();

        tempW->setDate(currentItem->getDate());
        tempW->setDescription(currentItem->getDescription());
        tempW->setTitre(currentItem->getNom());
        tempW->setEntete(monSet->getType()=="ensemble"?0:counter);
        counter++;

        if(currentItem->getType() == "tache")
        {
            tempW->setType(Widget::ELEMENT);
        }
        else
        {
            tempW->setType(Widget::LIST);
        }

        layout->addWidget(tempW,x,y,1,5);

        if(currentItem->getType()=="ensemble")
        {
            y++;
            Controleur::affichage(currentItem,layout);
            y--;
        }
        if(currentItem->getType()=="liste")
        {
            y++;
            Controleur::affichage(currentItem,layout);
            y--;
        }

    }
}

QScrollArea * Controleur::getScrollArea()
{
    //exp test
    Tache * num1 = new Tache("Tache 1", QDate::currentDate(), "Execution du chien",(Item *)root_);
    qDebug()<<"1";
    Liste * num2 = new Liste("Liste 2", QDate::currentDate(), "Quelques exécutions", (Item *)root_);
    qDebug()<<"2";
    Tache * num3 = new Tache("Tache 3", QDate::currentDate(), "Execution du lapin", (Item *)num2);
    qDebug()<<"1";
    Ensemble * num4 = new Ensemble("Ensemble 4", QDate::currentDate(), "Execution du chat", (Item *)num2);
    qDebug()<<"1";
    Tache * num6 = new Tache("Tache 6", QDate::currentDate(), "Execution du cadet", (Item *)num4);
    qDebug()<<"1";
    Tache * num5 = new Tache("Tache 5", QDate::currentDate(), "Execution du ..... du gamin !", (Item *)root_);
    qDebug()<<"1";


    ((Ensemble*)root_)->ajoutItem((Item *)num1);
    qDebug()<<"ajout n1";
        num2->ajoutItem((Item *)num3);
        num4->ajoutItem((Item *)num6);
        num2->ajoutItem((Item *)num4);
    ((Ensemble*)root_)->ajoutItem((Item *)num2);
    ((Ensemble*)root_)->ajoutItem((Item *)num5);

    qDebug()<<"fin example";
    //fin exp


    vue = new QScrollArea();
    centralLO = new QGridLayout();
    centralWO = new QWidget();

    x=0;
    y=0;
    affichage(root_,centralLO);

    centralWO->setLayout(centralLO);
    vue->setWidget(centralWO);
    //vue->setBackgroundRole(QPalette::Light);
    //vue->setStyleSheet("background-color:white;");
    return vue;

}
