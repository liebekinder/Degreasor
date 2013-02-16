#include "mywidget.h"

myWidget::myWidget(Controleur *control, QWidget *parent) :
    QScrollArea(parent)
{
    this->controler = control;
}

void myWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        qDebug()<<"bouton droit";
        QMenu * m = new QMenu();
            QMenu * a1 = m->addMenu("Ajouter &dans...");
                //a1->setStatusTip("ajouter un item inclus dans l'item selectionné");

                QAction * a11 = a1->addAction("Ajout d'une nouvelle &tache");
                connect(a11,SIGNAL(triggered()),controler,SLOT(addTacheApres()));

                QAction * a12 = a1->addAction("Ajout d'une &liste");
                connect(a12,SIGNAL(triggered()),controler,SLOT(addListeApres()));

                QAction * a13 = a1->addAction("Ajout d'un en&semble");
                connect(a13,SIGNAL(triggered()),controler,SLOT(addEnsembleApres()));

                QMenu * a14 = a1->addMenu("Ajout à partir d'un &template");
                //a13->setStatusTip("export de l'item vers un template");

                    QAction * a141 = a14->addAction("template &1");
                    connect(a141,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a142 = a14->addAction("template &2");
                    connect(a142,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a143 = a14->addAction("template &3");
                    connect(a143,SIGNAL(triggered()),controler,SLOT(addTache()));

                    a141->setDisabled(true);
                    a142->setDisabled(true);
                    a143->setDisabled(true);

            QMenu * a2 = m->addMenu("Ajouter &après...");
                //a2->setStatusTip("ajouter un item après l'item selectionné");
                a2->setDisabled(true);

            QAction * a3 = m->addAction("&Export vers template...");
                //a3->setStatusTip("export de l'item vers un template");
                a3->setDisabled(true);

        m->popup(event->globalPos());
    }
    else{

    }
    return;
}

