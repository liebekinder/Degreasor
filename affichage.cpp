#include "affichage.h"

Affichage::Affichage(QObject *parent) :
    QObject(parent)
{
}

Widget * Affichage::getCenterElem()
{
    return this->centerOn;
}

int Affichage::process(Item * monSet, QGridLayout * layout, Controleur * ctrl, Item * centerOn, bool afficher)
{
    //monSet = new Ensemble("Racine", QDate::currentDate(), "La racine de nos problèmes");

    Item * root;
    if(monSet->getType()=="ensemble") root = ((Ensemble *)monSet);
    else root = ((Liste *)monSet);


    QList<Item *>::iterator it;
    QList<Item *> * maListe = monSet->getType()=="ensemble" ? ((Ensemble *)root)->getNotreListe() :  ((Liste *)root)->getNotreListe() ;

    int moyenne = 0;
    int counter = 1;
    for(it= maListe->begin();it != maListe->end();++it)
    {
        x++;
        counter++;
        Item * currentItem = ((Item*)*it);

        //qDebug()<<"add to screen "+currentItem->getNom();
        //qDebug()<<(afficher==true?1:0);



        Widget * tempW = new Widget(ctrl,currentItem);

        if(currentItem->getType() == "tache") moyenne+=((Tache *)currentItem)->getPercentage();
        if(afficher)
        {

            if(centerOn==currentItem)
            {
                this->centerOn = tempW;
            }
            tempW->setDate(currentItem->getDate());
            tempW->setDescription(currentItem->getDescription());
            tempW->setTitre(currentItem->getNom());
            tempW->setEntete(monSet->getType()=="ensemble"?0:counter);

            if(currentItem->getType() == "tache")
            {
                tempW->setType(Widget::ELEMENT);
                tempW->setPercent(((Tache *)currentItem)->getPercentage());

            }
            else
            {
                tempW->setType(Widget::LIST);
            }

            layout->addWidget(tempW,x,y,1,5);
        }



        if(currentItem->getType()=="ensemble" )
        {
            y++;
            int perc = Affichage::process(currentItem,layout,ctrl,centerOn,currentItem->getVisible() && afficher);
            if(afficher) tempW->setPercent(perc);
            moyenne+=perc;
            y--;
        }
        if(currentItem->getType()=="liste")
        {
            y++;
            int perc = Affichage::process(currentItem,layout,ctrl,centerOn,currentItem->getVisible() && afficher);
            if(afficher) tempW->setPercent(perc);
            moyenne+=perc;
            y--;
        }

    }
    return counter==1?0:moyenne/(counter-1);
}

myWidget * Affichage::getScrollArea(Item * root_, Controleur *ctrl, Item *centerOn)
{



    vue = new myWidget(ctrl);
    vue->setFrameShape(QFrame::NoFrame);

    centralLO = new QGridLayout();
    centralWO = new QWidget();
    //monWidget = new myWidget(ctrl);
    //monWidgetL = new QVBoxLayout();


    x=0;
    y=0;
    process(root_,centralLO,ctrl,centerOn,true);

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
