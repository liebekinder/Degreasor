#include "droparea.h"

#include "item.h"
#include <QtWidgets>

DropArea::DropArea(QWidget *parent) :
    QWidget(parent)
{
     QPalette cpalette3 = palette();
     QBrush brush3(QColor(0, 255, 0, 255));
     brush3.setStyle(Qt::SolidPattern);
     cpalette3.setBrush(QPalette::Active, QPalette::Window, brush3);
     this->setPalette(cpalette3);
     this->setAutoFillBackground(true);
     //this->listeGeree=listeGeree;
     this->setAcceptDrops(true);
}

void DropArea::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"Entree dans la zone de drop";
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DropArea::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}

void DropArea::dropEvent(QDropEvent *event)
{
    qDebug()<<"Drop effectué  !";
    if (event->mimeData()->hasFormat("application/x-dnditemdata")) {
        QByteArray itemData = event->mimeData()->data("application/x-dnditemdata");
        QDataStream dataStream(&itemData, QIODevice::ReadOnly);

        //QPixmap pixmap = QPixmap(":/images/boat.png");;
        //QPoint offset;
        QString itemEnvoye;
        dataStream >> itemEnvoye;
        emit dropICI(itemEnvoye);

        //qDebug()<< "T'as drop "+itemEnvoye;
        //listeGeree->addItem(new QListWidgetItem(itemEnvoye));

        /*QLabel *newIcon = new QLabel(this);
        newIcon->setPixmap(pixmap);
        newIcon->move(event->pos() - offset);
        newIcon->show();
        newIcon->setAttribute(Qt::WA_DeleteOnClose);*/

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    } else {
        event->ignore();
    }
}
