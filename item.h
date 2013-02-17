#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QDate>

class Item : public QObject
{
    Q_OBJECT
public:
    Item(QString nom, QDate date, QString description, Item * conteneur, QObject *parent = 0);
    Item(Item * conteneur, QObject *parent = 0);
    Item(bool root, QObject *parent = 0);

    enum DateRelative{
        TwoWeeksBefore = -14,
        OneWeekBefore = -7,
        TwoDaysBefore = -2,
        OneDayBefore = -1,
        Now = 0,
        OneDayAfter = 1,
        TwoDaysAfter = 2,
        OneWeekAfter = 7,
        TwoWeeksAfter = 14};
    
    //fonctions


    void setType(QString t);
    QString getType();

    //accesseur

    QString getNom();
    QDate getDate();
    DateRelative getDateR();
    QString getDescription();
    QWidget * getVue();
    Item * getParent();
    bool getVisible();
    void setNom(QString n);
    void setDate(QDate d);
    void setDateR(DateRelative r);
    void setDescription(QString i);
    void setVue(QWidget * v);
    void setParent(Item * p);
    void setVisible(bool b);



private:
    bool visible;
    QString nom_;
    QDate date_;
    DateRelative dateR_;
    QString description_;
    Item * itemAssocie_;
    QList<Item *> * precondition_;

    Item * parent_;
    QString TYPE;
    QWidget * vue_;
signals:
    
public slots:
    
};

#endif // ITEM_H
