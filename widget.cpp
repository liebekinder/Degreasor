#include "widget.h"

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
    date->setText(dateText.currentDate().toString("dd/MM/yyyy"));
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
    //this->installEventFilter(this);

    this->currentPercent = 0;
    this->imageOf = caller;
    this->controler = ctrl;
    this->setFixedSize(500,100);

    connect(this, SIGNAL(addTacheALaSuiteDeTacheSignal(Item *)), controler, SLOT(addTacheALaSuiteDeTache(Item *)));
    connect(this, SIGNAL(addListeALaSuiteDeTacheSignal(Item *)), controler, SLOT(addListeALaSuiteDeTache(Item *)));
    connect(this, SIGNAL(addEnsembleALaSuiteDeTacheSignal(Item *)), controler, SLOT(addEnsembleALaSuiteDeTache(Item *)));

    connect(this, SIGNAL(addTacheApresTacheSignal(Item *)), controler, SLOT(addTacheApresTache(Item *)));
    connect(this, SIGNAL(addListeApresTacheSignal(Item *)), controler, SLOT(addListeApresTache(Item *)));
    connect(this, SIGNAL(addEnsembleApresTacheSignal(Item *)), controler, SLOT(addEnsembleApresTache(Item *)));


    chiffre = new entete(0,0);

    date = new QLabel();
    date->installEventFilter(this);
    date->setAlignment(Qt::AlignCenter);
    date->setFont(QFont("Arial", 12));

    titre = new QLabel();
    titre->installEventFilter(this);
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Arial", 15, QFont::Bold));
    titre->setMaximumSize(14/16.*500,50);

    description = new QLabel();
    description->installEventFilter(this);
    description->setAlignment(Qt::AlignCenter);
    QFont fDesc("Arial", 12);
    fDesc.setItalic(true);
    description->setFont(fDesc);
    description->setMaximumSize(2.7/3.5*500*14/16.,50);
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



    centralLayout = new QHBoxLayout();
    rightLayout= new QVBoxLayout();
    subRightLayout= new QHBoxLayout();

            subRightLayout->addWidget(date,1);
            subRightLayout->addWidget(lineH2);
            subRightLayout->addWidget(description,2.7);
        rightLayout->addWidget(titre);
        rightLayout->addWidget(lineH);
        rightLayout->addLayout(subRightLayout);
        rightLayout->setSpacing(0);
    centralLayout->addWidget(chiffre,1);
    centralLayout->addWidget(lineV);
    centralLayout->addLayout(rightLayout,15);
    centralLayout->setSpacing(1);

    this->setLayout(centralLayout);



    //chiffre->setContentsMargins(100,100,100,100);
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //QColor myColor(0,0,255);
    //QBrush myBrush(myColor);
    int rayonAngles = 20;
    QPen myPen(Qt::black, 2);
    int padding = 7;
    painter.setPen(myPen);
    painter.drawLine(padding+rayonAngles,padding,size().width()-(padding+rayonAngles),padding);
    painter.drawLine(padding+rayonAngles,size().height()-padding,size().width()-(padding+rayonAngles),size().height()-padding);
    painter.drawLine(padding,padding+rayonAngles,padding,size().height()-(padding+rayonAngles));
    painter.drawLine(size().width()-padding,padding+rayonAngles,size().width()-padding,size().height()-(padding+rayonAngles));

    painter.drawArc( size().width()-(padding+rayonAngles)-rayonAngles, padding, rayonAngles*2, rayonAngles*2, 0*16, 90*16);

    painter.drawArc( size().width()-(padding+rayonAngles)-rayonAngles,size().height()-(padding+rayonAngles)-rayonAngles, rayonAngles*2, rayonAngles*2, 270*16, 90*16);
    if(type==Widget::ELEMENT)
    {
        painter.drawArc( padding, padding, rayonAngles*2, rayonAngles*2, 90*16, 90*16); //rectangle//angle de départ, taille angulaire de l'arc
        painter.drawArc( padding, size().height()-(padding+rayonAngles)-rayonAngles, rayonAngles*2, rayonAngles*2, 180*16, 90*16);
    }
    else if(type==Widget::LIST)
    {
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
    if(e->type()==QEvent::MouseButtonPress)
    {
        this->mousePressEvent((QMouseEvent *)e);
        return true;
    }
    return false;

}


void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton && this->imageOf->getType()!="tache")
    {
        qDebug()<<"Double clic gauche !";
        this->imageOf->setVisible(!this->imageOf->getVisible());
        controler->callRefreshWithoutMoveScreen();
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{

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
                a14->setDisabled(true);

                    QAction * a141 = a14->addAction("template &1");
                    connect(a141,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a142 = a14->addAction("template &2");
                    connect(a142,SIGNAL(triggered()),controler,SLOT(addTache()));

                    QAction * a143 = a14->addAction("template &3");
                    connect(a143,SIGNAL(triggered()),controler,SLOT(addTache()));

                    a141->setDisabled(true);
                    a142->setDisabled(true);
                    a143->setDisabled(true);

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


            QAction * a3 = m->addAction("&Export vers template...");
                //a3->setStatusTip("export de l'item vers un template");
                a3->setDisabled(true);

        m->popup(event->globalPos());
    }
    else if(event->button() == Qt::LeftButton && type==Widget::ELEMENT)
    {
        this->currentPercent=this->currentPercent==0?100:0;
        this->setPercent(this->currentPercent);
        ((Tache*)this->imageOf)->setPercentage(currentPercent);
        controler->callRefreshWithoutMoveScreen();
    }
    else
    {

    }
    return;
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



