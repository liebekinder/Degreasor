#include "dragzone.h"
#include "widget.h"
#include <QDebug>

DragZone::DragZone(Widget *pere, QWidget *parent) :
    QWidget(parent)
{
    this->parent = pere;
    this->installEventFilter(this);
}

void DragZone::mousePressEvent(QMouseEvent *event){

    if(event->button() == Qt::LeftButton)
    {
        /*Item * oldSelect = controler->getSelectedItem();
        Widget * oldSelectW = controler->getSelectedWidget();
        controler->setSelectedItem(this->imageOf,this);
        if(oldSelect!=controler->getRoot()) oldSelectW->update();
        update();*/

        qDebug()<<"Debut dra1g";
        //QPoint  test = QPoint(this->pos());
        //Widget *child = static_cast<Widget*>(childAt(test));
        Widget *child = parent->getChild(event);

        //Widget *child = static_cast<Widget*>(childAt(this->pos()));
        if (!child)
            return;

        QPixmap pixmap; //= QPixmap(this->size());
        pixmap=parent->grab(QRect(0,0,parent->size().width(),parent->size().height()));
        QDrag *drag = new QDrag(this);
        QByteArray itemData;
        QDataStream dataStream(&itemData, QIODevice::WriteOnly);
        dataStream << parent->getImage()->getUID().toString();

        QMimeData *mimeData = new QMimeData;
        mimeData->setData("application/x-dnditemdata", itemData);


        drag->setMimeData(mimeData);
        drag->setPixmap(pixmap);
        drag->setHotSpot(event->pos() - child->pos());


        /*QPixmap tempPixmap = pixmap;
        QPainter painter(this);
        painter.begin(&tempPixmap);
        painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
        painter.end();*/

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
}

void DragZone::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPixmap px;

    if(parent->getImage()->getVisible())
    {
        if(parent->getImage()->getType()=="tache")
        {
            px.load(":/images/grabIcon.png");
        }
        else
        {
            px.load(":/images/grabIconMoins.png");
        }

    }
    else
    {
        px.load(":/images/grabIconPlus.png");
    }
    px=px.scaledToHeight(px.size().height()*parent->size().height()/500.,Qt::SmoothTransformation);
    painter.drawPixmap(QPoint(this->size().width()/2.,18*parent->size().height()/500.),px,px.rect());
}
