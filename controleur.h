#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include <QDebug>

#include "ensemble.h"
#include "item.h"

class Controleur : public QObject
{
    Q_OBJECT

public:
    explicit Controleur(QObject *parent = 0);
    Item * ensemble_;
    
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
