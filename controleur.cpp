#include "controleur.h"

#include "mainwindow.h"


Controleur::Controleur(MainWindow * theControlledWindow,QObject *parent) :
    QObject(parent)
{
    root_ = new Ensemble(true);
    selectedItem = root_;
    this->theControlledWindow = theControlledWindow;
    //root_ = new Ensemble("nom", QDate::currentDate(),"bla", NULL);
    //qDebug()<< Item::TwoDaysAfter;

}

Item * Controleur::getSelectedItem()
{
    return selectedItem;
}

void Controleur::setSelectedItem(Item * wi)
{
    selectedItem = wi;
    refreshRightPanel(wi);
    //methode d'affichage de la partie droite de l'ui
}

void Controleur::refreshRightPanel(Item * wi)
{
    //actualisation des combobox
    videCombo(theControlledWindow->cbb2);
    process(root_, theControlledWindow->cbb2);

    //nom
    theControlledWindow->le1->setText(wi->getNom());
    qDebug()<<"nom... done!";
    //choix de la date
    if(wi->getChoixDate()) theControlledWindow->cb1->setChecked(true);
    else theControlledWindow->cb2->setChecked(true);
    qDebug()<<"radiobutton... done!";
    //date
    theControlledWindow->de->setDate(wi->getDate());
    qDebug()<<"date... done!";
    //theControlledWindow->cbb1->setCurrentText(wi->getAssocie()->getDateRString(wi->getDateR()));
    qDebug()<<"combobox... done!";
    //ici, besoin d'une fonction qui détermine la position de l'item wi->getAssocie()
    //dans la combobox. Besoin d'une liste pour ce faire.
    //theControlledWindow->cbb2->setCurrentText(wi->getAssocie()->getNom());
    qDebug()<<"combobox2... done!";
    //description
    theControlledWindow->te->setText(wi->getDescription());
    qDebug()<<"text area... done!";

}

void Controleur::videCombo(QComboBox * c){
    for(int i=c->count()-1; i>=0;--i){
        c->removeItem(i);
    }
}

void Controleur::process(Item * item, QComboBox * c)
{
    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(item->getType() == "liste") maListe =( (Liste *)item)->getNotreListe();
    if(item->getType() == "ensemble") maListe =( (Ensemble *)item)->getNotreListe();

    qDebug()<<"iterateur... done!";
    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        qDebug()<<"un tour!... done!";
        Item * currentItem = ((Item*)*it);
        qDebug()<<currentItem;
        qDebug()<<"cast!... done!";
        qDebug()<<currentItem->getType();

        if(currentItem->getType() == "tache")
        {
            qDebug()<<"tache ajout... done!";
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            qDebug()<<"listez/ensemble ajout... done!";
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
            process(currentItem, c);
            qDebug()<<"listez/ensemble ajout... done!";
        }
    }
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
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté! Ensemble avant";
    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApres()
{
    Item * yeah = new Liste("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté!";
    theControlledWindow->refresh(yeah);
}

void Controleur::addTacheApres()
{
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
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
    this->setSelectedItem(yeah);

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
    this->setSelectedItem(yeah);

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
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addTacheApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsembleApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

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

