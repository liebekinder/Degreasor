#include "mywidget.h"

myWidget::myWidget(Controleur *control, QWidget *parent) :
    QScrollArea(parent)
{
    this->controler = control;
}

void myWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        qDebug()<<"bouton droit";
        QMenu * m = new QMenu();
            QMenu * a1 = m->addMenu("Ajouter...");
                //a1->setStatusTip("ajouter un item inclus dans l'item selectionné");

                QAction * a11 = a1->addAction("Ajout d'une nouvelle &tache");
                connect(a11,SIGNAL(triggered()),controler,SLOT(addTacheApres()));

                QAction * a12 = a1->addAction("Ajout d'une &liste");
                connect(a12,SIGNAL(triggered()),controler,SLOT(addListeApres()));

                QAction * a13 = a1->addAction("Ajout d'un en&semble");
                connect(a13,SIGNAL(triggered()),controler,SLOT(addEnsembleApres()));

                QMenu * a14 = a1->addMenu("Ajout à partir d'un &template");
                //a13->setStatusTip("export de l'item vers un template");


                mapper = new QSignalMapper(this);

                for(int i = 0;i<controler->listeTemplate->count();i++)
                {
                    QAction * tempAction = a14->addAction(controler->listeTemplate->at(i));
                    mapper->setMapping(tempAction, i);
                    // Associate the toggled signal to map slot from the mapper
                    // (it does not matter if we don't use the bool parameter from the signal)
                    connect(tempAction, SIGNAL(triggered()), mapper, SLOT(map()));
                }

                connect(mapper, SIGNAL(mapped(int)), this, SLOT(templateTest(int)));
                if(controler->listeTemplate->count()==0) a14->setDisabled(true);

            QMenu * a2 = m->addMenu("Ajouter &dans...");
                //a2->setStatusTip("ajouter un item après l'item selectionné");
                a2->setDisabled(true);
            m->addSeparator();

            QAction * a3 = m->addAction("&Export vers template...");
                //a3->setStatusTip("export de l'item vers un template");
                a3->setDisabled(true);



            m->addSeparator();
            m->addSeparator();
            QMenu * a4 = m->addMenu("Supprimer");

                QAction *a41 = a4->addAction("Supprimer Tout...");
                    connect(a41,SIGNAL(triggered()),this,SLOT(deleteThis()));
                    QMenu * a42 = a4->addMenu("supprimer Template...");

                    mapper3 = new QSignalMapper(this);

                    for(int b = 0;b<controler->listeTemplate->count();b++)
                    {
                        QAction * actionTemplate = a42->addAction(controler->listeTemplate->at(b));
                        mapper3->setMapping(actionTemplate, b);
                        // Associate the toggled signal to map slot from the mapper
                        // (it does not matter if we don't use the bool parameter from the signal)
                        connect(actionTemplate, SIGNAL(triggered()), mapper3, SLOT(map()));
                    }

                    connect(mapper3, SIGNAL(mapped(int)), this, SLOT(templateTest3(int)));

                    if(controler->listeTemplate->count()==0) a42->setDisabled(true);


        m->popup(event->globalPos());
    }
    else{
        controler->setSelectedItem(controler->getRoot());
        controler->refreshRightPanel(NULL, true);
        controler->callRefreshWithoutMoveScreen();

    }
    return;
}

void myWidget::templateTest(int i)
{
    Item * yeah = controler->chargerXml(QDir::currentPath()+"/templates/"+controler->listeTemplate->at(i),true);
    if(yeah!=NULL)
    {
        ((Ensemble*) controler->getRoot())->ajoutItem(yeah);

        controler->setSelectedItem(yeah);
        controler->refresh(yeah);
        qDebug()<<i;
    }
}

void myWidget::templateTest3(int i)
{
    qDebug() << "suppression template";

    QDir dir = QDir::currentPath()+"/templates";
    qDebug()<< dir.path()+"/"+controler->listeTemplate->at(i);
    dir.remove(dir.path()+"/"+controler->listeTemplate->at(i));
    controler->listerTemplate();
    controler->callRefreshWithoutMoveScreen();
}

void myWidget::toutReduire(Item * itemC)
{

    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(itemC->getType() == "liste") maListe =( (Liste *)itemC)->getNotreListe();
    if(itemC->getType() == "ensemble") maListe =( (Ensemble *)itemC)->getNotreListe();

    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        Item * currentItem = ((Item*)*it);
        currentItem->setVisible(false);

        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            toutReduire(currentItem);
        }

    }
}

void myWidget::deleteThis()
{
    controler->setRoot(new Ensemble(true));
    controler->callRefreshWithoutMoveScreen();
}

void myWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    toutReduire(controler->getRoot());
    qDebug()<< "uiohdsiodiohs";
}

