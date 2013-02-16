#ifndef LISTE_H
#define LISTE_H

#include <QObject>
#include <QDate>

#include "item.h"

class Liste : public Item
{
    Q_OBJECT
public:

    Liste(QString nom, QDate date, QString description, QObject *parent = 0);
    Liste(QObject *parent = 0);

    void ajoutItem(Item * it);

private:
    QList<Item *> * notreListe_;

signals:

public slots:

};

#endif // LISTE_H
