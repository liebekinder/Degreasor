#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QDate>
#include <QDebug>
#include <QUuid>
#include <QComboBox>

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
    bool getVisible();
    void setVisible(bool b);
    bool getChoixDate();
    void setChoixDate(bool b);
    QString getNom();
    void setNom(QString n);
    QDate getDate();
    void setDate(QDate d);
    DateRelative getDateR();
    void setDateR(DateRelative r);
    void setDescription(QString i);
    QString getDescription();
    QWidget * getVue();
    void setVue(QWidget * v);
    Item * getParent();
    void setAssocie(Item * i);
    Item * getAssocie();
    void setParent(Item * p);
    void setUID(QUuid i);
    QUuid getUID();
    QString getDateRString(DateRelative d);
    QList<Item *> * getPreconditions();
    void setPreconditions(QList<Item *> * pred);

    static void getComboBox(QComboBox *c);
    static DateRelative getComboBoxFromText(QString s);
private:
    bool visible;
    QString nom_;
    bool choixDate_;
    QDate date_;
    DateRelative dateR_;
    QString description_;
    Item * itemAssocie_;
    QList<Item *> * precondition_;
    QUuid UID;

    Item * parent_;
    QString TYPE;
    QWidget * vue_;
signals:
    
public slots:
    
};

#endif // ITEM_H
