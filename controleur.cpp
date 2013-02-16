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

        layout->addWidget(tempW,x,y,1,3);

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
    Tache * num1 = new Tache("Tache 1", QDate::currentDate(), "Execution du chien");
    Liste * num2 = new Liste("Liste 2", QDate::currentDate(), "Quelques exécutions");
    Tache * num3 = new Tache("Tache 3", QDate::currentDate(), "Execution du lapin");
    Ensemble * num4 = new Ensemble("Ensemble 4", QDate::currentDate(), "Execution du chat");
    Tache * num6 = new Tache("Tache 6", QDate::currentDate(), "Execution du cadet");
    Tache * num5 = new Tache("Tache 5", QDate::currentDate(), "Execution du ..... du gamin !");
    ((Ensemble*)ensemble_)->ajoutItem(num1);
        num2->ajoutItem(num3);
        num4->ajoutItem(num6);
        num2->ajoutItem(num4);
    ((Ensemble*)ensemble_)->ajoutItem(num2);
    ((Ensemble*)ensemble_)->ajoutItem(num5);
    //fin exp


    vue = new QScrollArea();
    centralLO = new QGridLayout();
    centralWO = new QWidget();

    x=0;
    y=0;
    affichage(ensemble_,centralLO);

    centralWO->setLayout(centralLO);
    vue->setWidget(centralWO);
    //vue->setBackgroundRole(QPalette::Light);
    //vue->setStyleSheet("background-color:white;");
    return vue;

}
