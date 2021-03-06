#include "mainwindow.h"

MainWindow::MainWindow(bool b, QWidget * parent) :
    QMainWindow(parent){
    qDebug()<<"mode console "<<b;

    Controleur * c = new Controleur(this);
    Q_UNUSED(c);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(920,480);
    setWindowTitle(tr("Degreasor!"));

    controler = new Controleur(this);
    controler->listerTemplate();

    ///////////////////////////////////
    //exp test
    /*Item * root_ = controler->getRoot();
    Tache * num1 = new Tache("Tache 1", QDate::currentDate(), "Execution du chien",(Item *)root_);
    Liste * num2 = new Liste("Liste 2", QDate::currentDate(), "Quelques exécutions", (Item *)root_);
    Tache * num3 = new Tache("Tache 3", QDate::currentDate(), "Execution du lapin", (Item *)num2);
    Ensemble * num4 = new Ensemble("Ensemble 4", QDate::currentDate(), "Execution du chat", (Item *)num2);
    Tache * num6 = new Tache("Tache 6", QDate::currentDate(), "Execution du cadet", (Item *)num4);
    Tache * num5 = new Tache("Tache 5", QDate::currentDate(), "Execution du ..... du gamin !", (Item *)root_);

    ((Ensemble*)root_)->ajoutItem((Item *)num1);
    qDebug()<<"ajout n1";
        num2->ajoutItem((Item *)num3);
        num4->ajoutItem((Item *)num6);
        num2->ajoutItem((Item *)num4);
    ((Ensemble*)root_)->ajoutItem((Item *)num2);
    ((Ensemble*)root_)->ajoutItem((Item *)num5);


        QList<Item *>* pred = new QList<Item *>();
        pred->append(num2);
        pred->append(num5);
        num6->setPreconditions(pred);

        qDebug()<< "ctoi buizazerffv" + controler->getItemWithUUID(num6->getUID().toString(),root_)->getNom();


    qDebug()<<"fin exemple";

    controler->saveToXml("example.xml");
    controler->saveToXml("templateExample.xml",num4,NULL,true);*/
    //fin exp
    Item * futurRoot = controler->chargerXml(QString("main.xml"));
    if(futurRoot!=NULL) controler->setRoot(futurRoot);

    //controler->chargerXml(QString("example.xml"));
    //qDebug()<<controler->chargerXml(QString("example.xml"));
    //((Ensemble*)controler->getRoot())->ajoutItem(controler->chargerXml(QString("example.xml")));

    ///////////////////////////////////

    central = new QWidget();
    centralL = new QVBoxLayout();

    upperPane = new QWidget();
    upperPaneL = new QVBoxLayout();
        upperPaneT = new QLabel();
        upperPaneL->addWidget(upperPaneT);
    upperPane->setLayout(upperPaneL);

    line = new QFrame();
    line->setFrameShape(QFrame::HLine);

    lowerPane = new QWidget();

        centralL->addWidget(upperPane,1);
        centralL->addWidget(line,1);
        lowerPaneL = new QHBoxLayout();

        //////////////////////////////////////////////////////

        /*vue = new myWidget(controler);
            vueL = new QVBoxLayout();
                QLabel * empty = new QLabel("- empty list -");
                vueL->addWidget(empty);
                vueL->setAlignment(Qt::AlignCenter);
            vue->setLayout(vueL);*/

        //affichage = new Affichage();
        vue = controler->getAffichage()->getScrollArea(controler->getRoot(), controler);

        stackedWidget = new QStackedWidget();
             stackedWidget->addWidget(vue);


        ///////////////////////////////////////////////////////
            line2 = new QFrame();
            line2->setFrameShape(QFrame::VLine);

            info = setInfoPanel(true);

            //lowerPaneL->addWidget(vue,7);
            lowerPaneL->addWidget(stackedWidget,7);
            lowerPaneL->addWidget(line2);
            lowerPaneL->addWidget(info,3);

        lowerPane->setLayout(lowerPaneL);

        centralL->addWidget(lowerPane,20);
    central->setLayout(centralL);

    setCentralWidget(central);

    //configuration

    QString date = "";
    date += QDate::longDayName(QDate::currentDate().dayOfWeek());
    date += " " + QString::number(QDate::currentDate().day());
    date += " " + QDate::longMonthName(QDate::currentDate().month());
    date += " " + QString::number(QDate::currentDate().year());
    upperPaneT->setText(date);
    upperPaneL->setAlignment(Qt::AlignHCenter);
    upperPaneT->setFont(QFont("Courrier", 20, 1));

    controler->refreshRightPanel(NULL, true);

    //actions

    b1->setDisabled(true);
    b2->setDisabled(true);
    connect(b1, SIGNAL(pressed()), controler, SLOT(cancelModification()));
    connect(b2, SIGNAL(pressed()), controler, SLOT(saveModification()));
    connect(((DropArea *)widg), SIGNAL(dropICI(QString)),controler, SLOT(getDrop(QString)));
    connect(dropListe,SIGNAL(itemClicked(QListWidgetItem*)),controler,SLOT(deleteItemListView(QListWidgetItem*)));
    connect(cbb1,SIGNAL(activated(int)),controler,SLOT(setRDButton(int)));
    connect(cbb2,SIGNAL(activated(int)),controler,SLOT(setRDButton(int)));
}

QWidget *MainWindow::setInfoPanel(bool b){
    info = new QWidget();
    infoL = new QVBoxLayout();

    if(b){
        hb1 = new QHBoxLayout();
        hb2 = new QHBoxLayout();
        hb3 = new QHBoxLayout();
        hb4 = new QVBoxLayout();

        vb1 = new QVBoxLayout();

        gb1 = new QGroupBox("Date: ");

        lb1 = new QLabel("Nom de la tâche: ");
        lb2 = new QLabel("L'évènement a lieu le ");
        lb3 = new QLabel("ou");
        lb4 = new QLabel("la tâche ");
        lb5 = new QLabel("Commentaires sur la tâche: ");
        lb6 = new QLabel("préconditions (tâche devant être accomplies avant la tâche courante): ");

        le1 = new QLineEdit();

        cb1 = new QRadioButton();
        cb2 = new QRadioButton();

        de = new QDateEdit(QDate::currentDate());

        cbb1 = new QComboBox();
        Item::getComboBox(cbb1);

        cbb2 = new QComboBox();

        te = new QTextEdit();
        ///////////////////////////

        dropListe = new QListWidget;
        widg = new DropArea();
        dropListeL = new QVBoxLayout();
        dropListeL->setMargin(0);
        dropListeL->addWidget(dropListe);
        widg->setLayout(dropListeL);

        //////////////////////////////
        widg->setMinimumHeight(75);

        b1 = new QPushButton("Annuler");
        b2 = new QPushButton("Sauvegarder");

            hb1->addWidget(lb1);
            hb1->addWidget(le1);
        infoL->addLayout(hb1);

                hb2->addWidget(cb1,1);
                hb2->addWidget(lb2,5);
                hb2->addWidget(de,5);
            vb1->addLayout(hb2);
            vb1->addWidget(lb3);
                hb3->addWidget(cb2,1);
                hb3->addWidget(cbb1,5);
                hb3->addWidget(lb4,2);
                hb3->addWidget(cbb2,5);
            vb1->addLayout(hb3);
            gb1->setLayout(vb1);
        infoL->addWidget(gb1);

        infoL->addWidget(lb5);
        infoL->addWidget(te,5);
        infoL->addWidget(lb6);
        infoL->addWidget(widg,2);

            hb4->addWidget(b2);
            hb4->addWidget(b1);

        infoL->addLayout(hb4,4);
    }


    b2->setMinimumHeight(40);
    info->setLayout(infoL);
    return info;
}

void MainWindow::refresh1(Item * centerOn)
{
    qDebug()<<"refresh";

    stackedWidget->removeWidget(vue);

    //delete vue;
    vue = controler->getAffichage()->getScrollArea(controler->getRoot(), controler, centerOn);

    stackedWidget->addWidget(vue);

    //Centrer la vue sur le dernier widget ajouté.
    if(centerOn!=NULL)
    {
        qDebug()<< controler->getAffichage()->getCenterElem()->geometry().y();
        int cPosy = controler->getAffichage()->getCenterElem()->geometry().y()- (vue->size().height())/2+controler->getAffichage()->getCenterElem()->size().height()/2;
        int cPosx = controler->getAffichage()->getCenterElem()->geometry().x()- (vue->size().width())/2+controler->getAffichage()->getCenterElem()->size().width()/2;
        vue->verticalScrollBar()->setValue(cPosy>0?cPosy:0);
        vue->horizontalScrollBar()->setValue(cPosx>0?cPosx:0);
        //qDebug()<< centerOn->geometry().x() + " "+ centerOn->geometry().y();
    }


    //stackedWidget->setCurrentIndex(0);

}

void MainWindow::callRefreshWithoutMoveScreen1()
{
    qDebug()<<"refresh2";

    stackedWidget->removeWidget(vue);

    int cPosy = vue->verticalScrollBar()->value();
    int cPosx = vue->horizontalScrollBar()->value();


    //delete vue;
    vue = controler->getAffichage()->getScrollArea(controler->getRoot(), controler, NULL);

    stackedWidget->addWidget(vue);

    vue->verticalScrollBar()->setValue(cPosy>0?cPosy:0);
    vue->horizontalScrollBar()->setValue(cPosx>0?cPosx:0);
    qDebug()<<"fin refresh";

}


MainWindow::~MainWindow()
{
}
