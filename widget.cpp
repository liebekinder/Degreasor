#include "widget.h"


void Widget::setPercent(int i)
{
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

void Widget::setDate(QDate *dateText)
{
    date->setText(dateText->currentDate().toString("dd/MM/yyyy"));
}

void Widget::setType(Type typeV)
{
    type = typeV;
    if(type==Widget::ELEMENT) chiffre->setType(0);
    else chiffre->setType(1);
    this->repaint();
}

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(500,100);

    chiffre = new entete(0,0);

    date = new QLabel();
    date->setAlignment(Qt::AlignCenter);
    date->setFont(QFont("Arial", 12));

    titre = new QLabel();
    titre->setAlignment(Qt::AlignCenter);
    titre->setFont(QFont("Arial", 15, QFont::Bold));
    titre->setMaximumSize(14/16.*500,50);

    description = new QLabel();
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

    lineV = new QFrame(this);
        //lineV->setGeometry(QRect(320, 150, 118000, 100));
        //lineV->setStyle();
        lineV->setFrameShape(QFrame::VLine);
    lineH = new QFrame(this);
         //lineH->setGeometry(QRect(320, 150, 1180000048, 100));
         lineH->setFrameShape(QFrame::HLine);
    lineH2 = new QFrame(this);
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

Widget::~Widget()
{
}


