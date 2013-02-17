#include "affichage.h"

Affichage::Affichage(QObject *parent) :
    QObject(parent)
{
}

void Affichage::process(Item * monSet, QGridLayout * layout, Controleur * ctrl)
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

        Widget * tempW = new Widget(ctrl,currentItem);

        tempW->setDate(currentItem->getDate());
        tempW->setDescription(currentItem->getDescription());
        tempW->setTitre(currentItem->getNom());
        tempW->setEntete(monSet->getType()=="ensemble"?0:counter);
        counter++;

        qDebug()<<"add to screen "+currentItem->getNom();

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
            Affichage::process(currentItem,layout,ctrl);
            y--;
        }
        if(currentItem->getType()=="liste")
        {
            y++;
            Affichage::process(currentItem,layout,ctrl);
            y--;
        }

    }
}

myWidget * Affichage::getScrollArea(Item * root_, Controleur *ctrl)
{

    vue = new myWidget(ctrl);
    vue->setFrameShape(QFrame::NoFrame);

    centralLO = new QGridLayout();
    centralWO = new QWidget();
    //monWidget = new myWidget(ctrl);
    //monWidgetL = new QVBoxLayout();


    x=0;
    y=0;
    process(root_,centralLO,ctrl);

    centralWO->setLayout(centralLO);
    vue->setWidget(centralWO);

    /*monWidgetL->addWidget(vue);*/
   // monWidget->setLayout(monWidgetL);


    //monWidget->setLayout(centralLO);
    //monWidgetL->addWidget(monWidget);
    //vue->setLayout(centralLO);
    //vue->setBackgroundRole(QPalette::Light);
    //vue->setStyleSheet("background-color:white;");
    return vue;

}
