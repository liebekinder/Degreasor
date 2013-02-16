#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QListIterator>

#include "ensemble.h"
#include "item.h"
#include "tache.h"
#include "liste.h"
#include "widget.h"

class Controleur : public QObject
{
    Q_OBJECT

public:
    Item * getRoot();
    explicit Controleur(QObject *parent = 0);
    Item * root_;

private:
signals:

public slots:
    void addEnsemble();
    void addListe();
    void addTache();
    void addEnsembleApres();
    void addListeApres();
    void addTacheApres();
};

#endif // CONTROLEUR_H
