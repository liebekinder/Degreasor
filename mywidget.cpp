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
            QAction * a4 = m->addAction("Supprimer");
                //a3->setStatusTip("export de l'item vers un template");
                //a3->setDisabled(true);
                connect(a4,SIGNAL(triggered()),this,SLOT(deleteThis()));


        m->popup(event->globalPos());
    }
    else{

    }
    return;
}

void myWidget::templateTest(int i)
{
    Item * yeah = controler->chargerXml(QDir::currentPath()+"/templates/"+controler->listeTemplate->at(i),true);

    qDebug() << "ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"+yeah->getNom();
    //((Ensemble*)root_)->ajoutItem(yeah);
    if(yeah!=NULL)
    {
        ((Ensemble*) controler->getRoot())->ajoutItem(yeah);
        //((Ensemble*)controler->getRoot())->ajoutItem(yeah);

        controler->setSelectedItem(yeah);
        controler->refresh(yeah);
        //controler->setRoot(yeah);
        //Controleur::parseAndAddAfter(root_, test ,yeah);
        qDebug()<<"test->getNom()";
        //controler->callRefreshWithoutMoveScreen();


        //Item * futurRoot = controler->chargerXml(QDir::currentPath()+"/templates/"+controler->listeTemplate->at(i));
        //if(futurRoot!=NULL) controler->setRoot(futurRoot);
        //controler->callRefreshWithoutMoveScreen();
        qDebug()<<i;
    }
    //emit addNewTemplate(this->imageOf);
}

void myWidget::deleteThis()
{
    controler->setRoot(new Ensemble(true));
    controler->callRefreshWithoutMoveScreen();
}

void myWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug()<< "uiohdsiodiohs";
}

