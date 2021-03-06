#include "entete.h"
#include "widget.h"



entete::entete(int numEntete,int typeV, Widget * papa,QWidget *parent) :
    QWidget(parent)
{
    type=typeV;
    percent = 0;
    numeroEntete = numEntete;
    this->papa = papa;
}

void entete::setPercent(int perc)
{
    if(perc<=100 && perc>=0) {
        percent = perc;
        this->repaint();
    }
}

void entete::setEntete(int numEntete)
{
    if(numEntete>=0) {
        numeroEntete = numEntete;
        this->repaint();
    }
}

void entete::setType(int typeV)
{
    type=typeV;
    this->repaint();
}

void entete::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    //painter.setRenderHint(QPainter::Antialiasing, true);

    //painter.setRenderHint(QPainter::Antialiasing, true);

    QPen myPen(Qt::black, 1);

    //plages de couleurs pour la barre de progression
    int rouge[20] = {241,255,255,255,255,255,255,255,255,252,227,227,190,146,146,57,57,22,51};
    int vert[20] = {0,55,101,101,169,169,216,229,229,255,255,255,255,255,255,255,255,233,204};

    int index = percent*0.18;

    //ma jolie barre de progression
    QColor myColor(rouge[index],vert[index],0);
    QBrush myBrush(myColor);
    myPen.setColor(myColor);
    painter.setPen(myPen);
    //painter.fillRect(0,(1.-percent/100.)*size().height(),size().width(),size().height()*percent/100.,myBrush);
    //double padding = (1.-percent/100.)*size().height();
    /*if(type==0)
    {
        padding = 0;
        double rayonAngles = (20+9-2)*papa->size().height()/100.;

        int i =0;
        while(i+padding<=rayonAngles)
        {
            if(i+padding<=rayonAngles) painter.drawLine(rayonAngles-qPow(qPow(rayonAngles,2)-qPow(rayonAngles-(i+padding),2),0.5),i+padding,size().width(),i+padding);
            i++;
        }

        painter.fillRect(0,rayonAngles+1,this->size().width(),size().height()-2*rayonAngles-2,myBrush);

        i=size().height()-rayonAngles;
        while(i<this->size().height())
        {
            painter.drawLine(rayonAngles-qPow(qPow(rayonAngles,2)-qPow((i+padding)-(size().height()-rayonAngles),2),0.5),i+padding,size().width(),i+padding);
            i++;
        }*/

        /*for(int i = 0;i<this->size().height();i++)//2*size().height()*percent/100.;i++)
        {
            //qDebug()<<qPow(rayonAngles-(i+padding),2);
            //if(i+padding<rayonAngles) painter.drawLine(qPow(qPow(rayonAngles,2)-qPow((i+padding),2),0.5),i+padding,size().width(),i+padding);
            if(i+padding<=rayonAngles) painter.drawLine(rayonAngles-qPow(qPow(rayonAngles,2)-qPow(rayonAngles-(i+padding),2),0.5),i+padding,size().width(),i+padding);
            else if(i+padding>=size().height()-rayonAngles) painter.drawLine(rayonAngles-qPow(qPow(rayonAngles,2)-qPow((i+padding)-(size().height()-rayonAngles),2),0.5),i+padding,size().width(),i+padding);
            else painter.drawLine(0,i+padding,size().width(),i+padding);

        }
    }*/
    if(type!=0)
    {
        painter.fillRect(0,(1.-percent/100.)*size().height(),size().width(),size().height()*percent/100.,myBrush);
    }


    //on dessine le symbole d'entête


    QFont font = QApplication::font();
    font.setPixelSize( size().height()/4 );
    myPen.setColor(Qt::black);
    painter.setPen(myPen);
    painter.setFont( font );
    if(numeroEntete==0)
    {
        painter.fillRect(size().width()/3.,size().height()/2.-size().width()/6.,size().width()/3.,size().width()/3.,Qt::black);
    }
    else
    {
        painter.drawText(QPoint(size().width()/(numeroEntete<10?3:5),6*size().height()/10.),QString::number(numeroEntete));
    }


    QPixmap px =  QPixmap();
    if(papa->getImage()->getType()!="tache")
    {
        if(papa->getImage()->getVisible())
        {
            if(papa->getControleur()->getSelectedItem()==papa->getImage())
            {
                px=papa->getControleur()->getPixmapMoinsBlanc();

            }
            else
            {
                px=papa->getControleur()->getPixmapMoinsNoir();

            }



        }
        else
        {
            if(papa->getControleur()->getSelectedItem()==papa->getImage())
            {
                px=papa->getControleur()->getPixmapPlusBlanc();

            }
            else
            {
                px=papa->getControleur()->getPixmapPlusNoir();

            }

        }

        //px=px.scaledToHeight(px.size().height()*papa->size().height()/500.,Qt::SmoothTransformation);
        painter.drawPixmap(QPoint(this->size().width()/2.-px.size().width()/2.,5*papa->size().height()/50.),px,px.rect());
    }



    /*//On efface l'angle de la progress barre.
    int rayon=20;
    for(int i =0;i<rayon;i++)
    {
        QColor myColor(0,0,255,255);
        myPen.setColor(myColor);
        painter.setPen(myPen);
        for(int j=0;j<rayon;j++)
        {


            if((rayon-i)*(rayon-i) + (rayon-j)*(rayon-j)>rayon*rayon) painter.drawPoint(i,size().height()-j);
        }
    }*/

}

void entete::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
