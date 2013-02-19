#include "widget.h"
#include <QMessageBox>
#include "mainwindow.h"

void Widget::setPercent(int i)
{
    this->currentPercent = i;
    chiffre->setPercent(i);
}

void Widget::setEntete(int i)
{
    chiffre->setEntete(i);
}

void Widget::setTitre(QString title)
{
    titre->setText(title);
}

void Widget::setDescription(QString descriptionText)
{
    description->setText(descriptionText);
}

void Widget::setDate(QDate dateText)
{
    Q_UNUSED(dateText);
    date->setText(dateText.currentDate().toString("dd/MM/yyyy"));
}

Item * Widget::getImage()
{
    return imageOf;
}

void Widget::setType(Type typeV)
{
    type = typeV;
    if(type==Widget::ELEMENT) chiffre->setType(0);
    else chiffre->setType(1);
    this->repaint();
}

Widget::Widget(Controleur *ctrl, Item *caller, QWidget *parent) :
    QWidget(parent)
{
    this->installEventFilter(this);


    setAttribute(Qt::WA_TranslucentBackground,true);

    this->currentPercent = 0;
    this->imageOf = caller;
    this->controler = ctrl;
    this->setFixedSize(0,50);
    //this->setFixedWidth(500*this->size().height()/100.);
    this->setFixedWidth(500*this->size().height()/100.*1.3);

    connect(this, SIGNAL(addTacheALaSuiteDeTacheSignal(Item *)), controler, SLOT(addTacheALaSuiteDeTache(Item *)));
    connect(this, SIGNAL(addListeALaSuiteDeTacheSignal(Item *)), controler, SLOT(addListeALaSuiteDeTache(Item *)));
    connect(this, SIGNAL(addEnsembleALaSuiteDeTacheSignal(Item *)), controler, SLOT(addEnsembleALaSuiteDeTache(Item *)));

    connect(this, SIGNAL(addTacheApresTacheSignal(Item *)), controler, SLOT(addTacheApresTache(Item *)));
    connect(this, SIGNAL(addListeApresTacheSignal(Item *)), controler, SLOT(addListeApresTache(Item *)));
    connect(this, SIGNAL(addEnsembleApresTacheSignal(Item *)), controler, SLOT(addEnsembleApresTache(Item *)));

    //connect(this, SIGNAL(addNewTemplate(Item *)),controler,SLOT(addNewTemplateC(Item *)));

    chiffre = new entete(0,0,this);
    chiffre->installEventFilter(this);

    date = new QLabel();
    date->installEventFilter(this);
    date->setAlignment(Qt::AlignCenter);
    //qDebug()<<this->size().height()/100.;
    date->setFont(QFont("Arial", 12*1.5*this->size().height()/100.));

    titre = new QLabel();
    titre->installEventFilter(this);
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Arial", 15*1.5*this->size().height()/100., QFont::Bold));
    titre->setMaximumSize(14/16.*this->size().width(),50*this->size().height()/100.);
    qDebug()<<50*this->size().height()/100.;
    //////////////////
    /*QPalette cpalette3 = palette();
    QBrush brush3(QColor(0, 255, 0, 255));
    brush3.setStyle(Qt::SolidPattern);
    cpalette3.setBrush(QPalette::Active, QPalette::Window, brush3);
    titre->setPalette(cpalette3);
    titre->setAutoFillBackground(true);*/
    //////////////////

    description = new QLabel();
    /*if(this->imageOf->getType()!="tache")*/ description->installEventFilter(this);
    description->setAlignment(Qt::AlignCenter);
    QFont fDesc("Arial", 12*1.5*this->size().height()/100.);//12*this->size().height()/250);
    fDesc.setItalic(true);
    description->setFont(fDesc);
    description->setMaximumSize(2.7/3.5*this->size().width()*14/16.,50*this->size().height()/100.);
       /* QPalette cpalette3 = palette();
        QBrush brush3(QColor(0, 255, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        cpalette3.setBrush(QPalette::Active, QPalette::Window, brush3);
        description->setPalette(cpalette3);
        description->setAutoFillBackground(true);*/

    lineV = new QFrame();
    lineV->installEventFilter(this);
        //lineV->setGeometry(QRect(320, 150, 118000, 100));
        //lineV->setStyle();
        lineV->setFrameShape(QFrame::VLine);
    lineH = new QFrame();
    lineH->installEventFilter(this);
         //lineH->setGeometry(QRect(320, 150, 1180000048, 100));
         lineH->setFrameShape(QFrame::HLine);
    lineH2 = new QFrame();
    lineH2->installEventFilter(this);
        //lineH2->setGeometry(QRect(320, 150, 118000, 100));
        lineH2->setFrameShape(QFrame::VLine);



    rightLayoutHight = new QHBoxLayout();
    rightLayoutHight->installEventFilter(this);
    rightLayoutHight->setMargin(0);
    rightLayoutHightContainer=new QWidget();
    rightLayoutHightContainer->setMaximumHeight(50*this->size().height()/100.);
    rightLayoutHightContainer->installEventFilter(this);


    dragZone = new DragZone(this);
    dragZone->setMaximumHeight(50*this->size().height()/100.);
        /*QPalette cpalette3 = palette();
        QBrush brush3(QColor(0, 255, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        cpalette3.setBrush(QPalette::Active, QPalette::Window, brush3);
        dragZone->setPalette(cpalette3);
        dragZone->setAutoFillBackground(true);*/


    centralLayout = new QHBoxLayout();
    centralLayout->installEventFilter(this);
    rightLayout= new QVBoxLayout();
    rightLayout->setMargin(0);
    rightLayout->installEventFilter(this);
    subRightLayout= new QHBoxLayout();
    subRightLayout->setMargin(0);
    subRightLayout->installEventFilter(this);

                rightLayoutHight->addWidget(titre,5);
                //if(this->imageOf->getType()=="tache")
                //{
                    rightLayoutHight->addWidget(dragZone,1);
                /*}
                else if(!this->imageOf->getVisible())
                {
                    QLabel * reDe = new QLabel("Liste repliée");
                    reDe->setMaximumHeight(50*this->size().height()/100.);
                    rightLayoutHight->addWidget(reDe,1);
                }
                else
                {
                    QLabel * reDe = new QLabel("Liste dépliée");
                    reDe->setMaximumHeight(50*this->size().height()/100.);
                    rightLayoutHight->addWidget(reDe,1);
                }*/

            rightLayoutHightContainer->setLayout(rightLayoutHight);

            subRightLayout->addWidget(date,1);
            subRightLayout->addWidget(lineH2);
            subRightLayout->addWidget(description,2.7);
        rightLayout->addWidget(rightLayoutHightContainer);
        rightLayout->addWidget(lineH);
        rightLayout->addLayout(subRightLayout);
        rightLayout->setSpacing(0);
    centralLayout->addWidget(chiffre,1);
    centralLayout->addWidget(lineV);
    centralLayout->addLayout(rightLayout,15);
    centralLayout->setSpacing(1*this->size().height()/100.);

    centralLayout->setMargin(3*this->size().height()/70.);
    this->setLayout(centralLayout);



    //chiffre->setContentsMargins(100,100,100,100);
}

Widget * Widget::getChild(QMouseEvent * event)
{
    return static_cast<Widget*>(childAt(event->pos()));
}

void Widget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    /////////////////////
    QPixmap px;

    //qDebug() <<QCoreApplication::applicationDirPath()+"/images/fondCourantElem.png";
    if(this->imageOf->getType()=="tache")
    {
        if(imageOf==controler->getSelectedItem())
        {
            //px.load(QCoreApplication::applicationDirPath()+"/images/fondCourantElemS.png");

            if(((Tache*)this->imageOf)->getPercentage()==100)
            {
                 px.load(":/images/fondCourantElemSelectS.png");
            }
            else
            {
                 px.load(":/images/fondCourantElemDeselectS.png");
            }
        }
        else
        {
            if(((Tache*)this->imageOf)->getPercentage()==100)
            {
                 px.load(":/images/fondCourantElemSelect.png");
            }
            else
            {
                 px.load(":/images/fondCourantElemDeselect.png");
            }
        }
    }
    else
    {
        if(imageOf==controler->getSelectedItem())
        {
            px.load(":/images/fondCourantListeS.png");
        }
        else
        {
            px.load(":/images/fondCourantListe.png");
        }
    }


    px=px.scaledToHeight(this->size().height()*px.size().height()/308.,Qt::SmoothTransformation);

    painter.drawPixmap(px.rect(),px);
    ////////////////////

    //QColor myColor(0,0,255);
    //QBrush myBrush(myColor);
    int padding = 0;
    int rayonAngles = (20+9-padding)*this->size().height()/100.;

    int partieLigneBoufeeParAngles = 0;
    int lineThin = size().height()/100.;

    painter.setPen(QPen(Qt::black, 2*size().height()/50.));
    painter.drawLine(padding+rayonAngles,padding,size().width()-(padding+rayonAngles),padding);
    painter.drawLine(padding+rayonAngles,size().height()-padding,size().width()-(padding+rayonAngles),size().height()-padding);
    painter.drawLine(padding,padding+rayonAngles,padding,size().height()-(padding+rayonAngles));
    painter.drawLine(size().width()-padding,padding+rayonAngles,size().width()-padding,size().height()-(padding+rayonAngles));

    painter.setPen(QPen(Qt::black, 1*size().height()/50.));



    painter.drawArc( size().width()-(padding+rayonAngles)-rayonAngles-partieLigneBoufeeParAngles-lineThin, padding+lineThin, rayonAngles*2, rayonAngles*2, 0*16, 90*16);

    painter.drawArc( size().width()-(padding+rayonAngles)-rayonAngles-partieLigneBoufeeParAngles-lineThin,size().height()-(padding+rayonAngles)-rayonAngles-lineThin, rayonAngles*2, rayonAngles*2, 270*16, 90*16);
    if(type==Widget::ELEMENT)
    {
        painter.drawArc( padding+partieLigneBoufeeParAngles+lineThin, padding+lineThin, rayonAngles*2, rayonAngles*2, 90*16, 90*16); //rectangle//angle de départ, taille angulaire de l'arc
        painter.drawArc( padding+partieLigneBoufeeParAngles+lineThin, size().height()-(padding+rayonAngles)-rayonAngles-lineThin, rayonAngles*2, rayonAngles*2, 180*16, 90*16);
    }
    else if(type==Widget::LIST)
    {
        painter.setPen(QPen(Qt::black, 2*size().height()/50.));
        painter.drawLine(padding,padding,padding,padding+rayonAngles);
        painter.drawLine(padding,padding,padding+rayonAngles,padding);

        painter.drawLine(padding,size().height()-(padding+rayonAngles),padding,size().height()-padding);
        painter.drawLine(padding,size().height()-padding,padding+rayonAngles,size().height()-padding);
    }

    //painter.drawRect(9,9,size().width()-18,size().height()-18);


}

bool Widget::eventFilter( QObject *, QEvent *e)
{

    if(e->type()==QEvent::MouseButtonDblClick)
    {
        this->mouseDoubleClickEvent((QMouseEvent *)e);
        return true;
    }
    if(e->type()==QEvent::MouseButtonRelease)
    {
        this->mouseReleaseEvent((QMouseEvent *)e);
        return true;
    }
    /*if(e->type()==QEvent::MouseButtonPress)
    {
        Item * oldSelect = controler->getSelectedItem();
        Widget * oldSelectW = controler->getSelectedWidget();
        controler->setSelectedItem(this->imageOf,this);
        if(oldSelect!=controler->getRoot()) oldSelectW->update();
        update();
        //this->mousePressEvent((QMouseEvent *)e);
        return true;
    }*/
    return false;

}

/*void Widget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Drag start";
    Widget *child = static_cast<Widget*>(childAt(event->pos()));
         if (!child)
             return;

     QPixmap pixmap = QPixmap(":/images/boat.png");

     QByteArray itemData;
     QDataStream dataStream(&itemData, QIODevice::WriteOnly);
     dataStream << pixmap << QPoint(event->pos() - child->pos());

     QMimeData *mimeData = new QMimeData;
          mimeData->setData("application/x-dnditemdata", itemData);
          QDrag *drag = new QDrag(this);
              drag->setMimeData(mimeData);
              drag->setPixmap(pixmap);
              drag->setHotSpot(event->pos() - child->pos());
}*/

////////////////////////////////////////////////

//void Widget::mousePressEvent(QMouseEvent *event)

/*void Widget::mousePressEvent(QMouseEvent *event){

    if(this->imageOf->getType()=="tache" && event->button() == Qt::LeftButton)
    {


        qDebug()<<"Debut drag";
        //QPoint  test = QPoint(this->pos());
        //Widget *child = static_cast<Widget*>(childAt(test));
        Widget *child = static_cast<Widget*>(childAt(event->pos()));

        //Widget *child = static_cast<Widget*>(childAt(this->pos()));
        if (!child)
            return;

        QPixmap pixmap; //= QPixmap(this->size());
        pixmap=this->grab(QRect(0,0,this->size().width(),this->size().height()));
        QDrag *drag = new QDrag(this);
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << this->imageOf->getNom();

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);


        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());




        //child->setPixmap(tempPixmap);
        qDebug()<<"Int drag";
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction) {
            //child->close(); //faudrais pas supprimer le widget....
        } else {
           // child->show();
            //on atterit ici si on ne drop pas le widget au bon endroit.
            qDebug()<<"raganrok drag";
            //child->setPixmap(pixmap);
        }
        qDebug()<<"Fin drag";
    }
}*/

///////////////////////////////////////////

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{

        //controler->getSelectedWidget()->setSelected(false);
        //controler->getSelectedWidget()->repaint();
        //controler->getSelectedWidget()->imageOf->setSelected(false);
        //controler->setSelectedItem(imageOf);


    qDebug()<<"Double clic gauche !";
    if(event->button()==Qt::LeftButton && this->imageOf->getType()!="tache")
    {

        this->imageOf->setVisible(!this->imageOf->getVisible());
        controler->setSelectedItem(imageOf);
        controler->callRefreshWithoutMoveScreen();
    }
    else if(event->button() == Qt::LeftButton && type==Widget::ELEMENT)
    {
        this->currentPercent=this->currentPercent==0?100:0;
        this->setPercent(this->currentPercent);
        ((Tache*)this->imageOf)->setPercentage(currentPercent);
        controler->setSelectedItem(imageOf);
        controler->callRefreshWithoutMoveScreen();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"qsdqsdqsdqsdqsdqsdqsd";
    if(event->button() == Qt::RightButton)
    {
        qDebug()<<"bouton droit";
        QMenu * m = new QMenu();
            QMenu * a1 = m->addMenu("Ajouter &après...");
                //a1->setStatusTip("ajouter un item inclus dans l'item selectionné");

                QAction * a11 = a1->addAction("Ajout d'une nouvelle &tache");
                //connect(a11,SIGNAL(triggered()),controler,SLOT(addTacheApresTache()));
                connect(a11,SIGNAL(triggered()),this,SLOT(addTacheALaSuiteDeTache()));

                QAction * a12 = a1->addAction("Ajout d'une &liste");
                connect(a12,SIGNAL(triggered()),this,SLOT(addListeALaSuiteDeTache()));
                //a12->setDisabled(true);

                QAction * a13 = a1->addAction("Ajout d'un en&semble");
                connect(a13,SIGNAL(triggered()),this,SLOT(addEnsembleALaSuiteDeTache()));
                //a13->setDisabled(true);

                QMenu * a14 = a1->addMenu("Ajout à partir d'un &template");
                //a13->setStatusTip("export de l'item vers un template");
                //a14->setDisabled(true);
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


                   /* QAction * a141 = a14->addAction("template &1");
                    connect(a141,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a142 = a14->addAction("template &2");
                    connect(a142,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a143 = a14->addAction("template &3");
                    connect(a143,SIGNAL(triggered()),controler,SLOT(addTache()));

                    a141->setDisabled(true);
                    a142->setDisabled(true);
                    a143->setDisabled(true);*/

            QMenu * a2 = m->addMenu("Ajouter &dans...");
                //a2->setStatusTip("ajouter un item après l'item selectionné");
                QAction * a21 = a2->addAction("...une nouvelle &tache");
                //connect(a11,SIGNAL(triggered()),controler,SLOT(addTacheApresTache()));
                connect(a21,SIGNAL(triggered()),this,SLOT(addTacheApresTache()));

                QAction * a22 = a2->addAction("...une nouvelle &liste");
                connect(a22,SIGNAL(triggered()),this,SLOT(addListeApresTache()));
                //a12->setDisabled(true);

                QAction * a23 = a2->addAction("...un nouvel en&semble");
                connect(a23,SIGNAL(triggered()),this,SLOT(addEnsembleApresTache()));
                //a13->setDisabled(true);

                if(imageOf->getType()=="tache") a2->setDisabled(true);

            m->addSeparator();
            QAction * a3 = m->addAction("&Export vers template...");
                //a3->setStatusTip("export de l'item vers un template");
                //a3->setDisabled(true);
                connect(a3,SIGNAL(triggered()),this,SLOT(exportTemplate()));
                if(this->imageOf->getType()=="tache") a3->setDisabled(true);
            m->addSeparator();
            m->addSeparator();
            QAction * a4 = m->addAction("Supprimer");
                //a3->setStatusTip("export de l'item vers un template");
                //a3->setDisabled(true);
                connect(a4,SIGNAL(triggered()),this,SLOT(deleteThis()));

        m->popup(event->globalPos());
    }
    else if(event->button() == Qt::LeftButton)
    {
        controler->setSelectedItem(imageOf);
        controler->callRefreshWithoutMoveScreen();

         ////////////////////////////////////////////////////////
                //Ici édition
         ///////////////////////////
    }
    else
    {

    }
    return;
}

void Widget::deleteThis()
{
    controler->saveToXml("tempSaveToDelete",controler->getRoot(),this->imageOf);
    Item * newRoot = controler->chargerXml("tempSaveToDelete");
    if(newRoot!=NULL)
    {
        controler->setRoot(newRoot);
        controler->callRefreshWithoutMoveScreen();
    }
}

void Widget::exportTemplate()
{
    if(controler->saveToXml(QDir::currentPath()+"/templates/"+QString(this->imageOf->getNom())+".template",this->imageOf,NULL,true))
    {
        QMessageBox::information(this,"Opération réussie.","Le template "+QString(this->imageOf->getNom())+" a bien été crée.");
        controler->listerTemplate();
        controler->callRefreshWithoutMoveScreen();
    }
    else
    {
        QMessageBox::warning(this,"Opération échouée !","Erreur lors de la création du fichier. Vérifiez votre nom de tâche.");
    }
}

void Widget::templateTest(int i)
{
    Item * yeah = controler->chargerXml(QDir::currentPath()+"/templates/"+controler->listeTemplate->at(i),true);

    qDebug() << "ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"+yeah->getNom();
    //((Ensemble*)root_)->ajoutItem(yeah);
    if(yeah!=NULL)
    {
        if(this->imageOf->getParent()->getType()=="ensemble")
        {
            ((Ensemble*) this->imageOf->getParent())->ajoutItem(yeah);
            //((Ensemble*)controler->getRoot())->ajoutItem(yeah);
        }
        else
        {
            ((Liste*) this->imageOf->getParent())->ajoutItem(yeah);
            //((Ensemble*)controler->getRoot())->ajoutItem(yeah);

        }
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

void Widget::addTacheALaSuiteDeTache()
{
    qDebug()<<"test1";
    emit addTacheALaSuiteDeTacheSignal(this->imageOf);
}

void Widget::addListeALaSuiteDeTache()
{
    qDebug()<<"test2";
    emit addListeALaSuiteDeTacheSignal(this->imageOf);
}

void Widget::addEnsembleALaSuiteDeTache()
{
    qDebug()<<"test3";
    emit addEnsembleALaSuiteDeTacheSignal(this->imageOf);
}

void Widget::addTacheApresTache()
{
    qDebug()<<"test11";
    emit addTacheApresTacheSignal(this->imageOf);
}

void Widget::addListeApresTache()
{
    qDebug()<<"test21";
    emit addListeApresTacheSignal(this->imageOf);
}

void Widget::addEnsembleApresTache()
{
    qDebug()<<"test31";
    emit addEnsembleApresTacheSignal(this->imageOf);
}

Widget::~Widget()
{
}
