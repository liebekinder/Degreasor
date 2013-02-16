#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QDate>

class Item : public QObject
{
    Q_OBJECT
public:
    Item(QString nom, QDate date, QString description, QObject *parent = 0);
    Item(QObject *parent);

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

    //accesseur

    QString getNom();
    QDate getDate();
    DateRelative getDateR();
    QString getDescription();
    void setNom(QString n);
    void setDate(QDate d);
    void setDateR(DateRelative r);
    void setDescription(QString i);
private:
    QString nom_;
    QDate date_;
    DateRelative dateR_;
    QString description_;
    Item * itemAssocie_;
    QList<Item *> precondition_;


    QString TYPE;
signals:
    
public slots:
    
};

#endif // ITEM_H
