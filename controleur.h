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


class MainWindow;
class Widget;

class Controleur : public QObject
{
    Q_OBJECT

public:
    Item * getRoot();
    Item * getSelectedItem();
    void setSelectedItem(Item *wi);
    void callRefreshWithoutMoveScreen();
    //void parseAndAddAfter(Item * currentList, Item *elementPere, Item * elementToAdd);
    explicit Controleur(MainWindow *theControlledWindow, QObject *parent = 0);
    Item * root_;


private:
    Item * selectedItem;
    MainWindow * theControlledWindow;
signals:
public slots:
    void addEnsemble();
    void addListe();
    void addTache();
    void addEnsembleApres();
    void addListeApres();
    void addTacheApres();
    void addTacheApresTache(Item *);
    void addListeApresTache(Item *);
    void addEnsembleApresTache(Item *);
    void addTacheALaSuiteDeTache(Item *);
    void addListeALaSuiteDeTache(Item *);
    void addEnsembleALaSuiteDeTache(Item *);
};

#endif // CONTROLEUR_H
