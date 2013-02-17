#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QFrame>
#include <QPaintEvent>
#include <QDate>
#include <QDebug>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QTimer>

#include <QPixmap>

#include "controleur.h"
#include "entete.h"
#include "item.h"
#include "dragzone.h"


QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    enum Type
        {
            ELEMENT = 0,
            LIST = 1
        };
    void setPercent(int i);
    void setEntete(int i);
    void setTitre(QString title);
    void setDate(QDate dateText);
    void setType(Type typeV);
    void setDescription(QString descriptionText);

    Item * getImage();
    Widget* getChild(QMouseEvent * event);



    //bool eventFilter(QObject *o,QEvent *e);

    explicit Widget(Controleur *control, Item * caller, QWidget *parent = 0);
    ~Widget();
protected:
    //void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

    bool eventFilter( QObject *, QEvent *e);
    void paintEvent(QPaintEvent *event);

public slots:
    void addTacheApresTache();
    void addListeApresTache();
    void addEnsembleApresTache();
    void addTacheALaSuiteDeTache();
    void addListeALaSuiteDeTache();
    void addEnsembleALaSuiteDeTache();
signals:
    void addTacheApresTacheSignal(Item *);
    void addListeApresTacheSignal(Item *);
    void addEnsembleApresTacheSignal(Item *);
    void addTacheALaSuiteDeTacheSignal(Item *);
    void addListeALaSuiteDeTacheSignal(Item *);
    void addEnsembleALaSuiteDeTacheSignal(Item *);
private:
    DragZone * dragZone;
    QHBoxLayout *rightLayoutHight;
    QWidget * rightLayoutHightContainer;


    int currentPercent;
    Item * imageOf;
    Controleur * controler;
    QHBoxLayout * centralLayout;
    QVBoxLayout * rightLayout;
    QHBoxLayout * subRightLayout;

    entete * chiffre;
    QLabel * titre;
    QLabel * date;
    QLabel * description;
    QFrame * lineV;
    QFrame * lineH;
    QFrame * lineH2;
    Type type;
};

#endif // WIDGET_H
