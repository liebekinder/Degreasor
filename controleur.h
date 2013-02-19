#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include <QObject>
#include <QDebug>
#include <QList>
#include <QListIterator>
#include <QComboBox>
#include <QDomDocument>
#include <QDomNode>
#include <QDomText>
#include <QFileSystemModel>
#include <QListWidgetItem>

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
    void setRoot(Item * root);
    Item * getSelectedItem();
    void setSelectedItem(Item *wi);
    void callRefreshWithoutMoveScreen();
    void refreshRightPanel(Item *wi, bool b = false);
    //void parseAndAddAfter(Item * currentList, Item *elementPere, Item * elementToAdd);
    explicit Controleur(MainWindow *theControlledWindow, QObject *parent = 0);
    Item * root_;
    bool saveToXml(QString path, Item * racine = NULL, Item *deleteItem = NULL, bool templateItem = false);
    void parseToXml(Item * item, QDomElement currentNode, QDomDocument * xml, Item *deleteItem);
    QDomElement creeXmlItem(Item * itemPh,QDomDocument * xml);
    Item * chargerXml(QString path, bool templateP=false);
    //void buildItemViaXml(QDomElement rootXml, Item *elementToBuild);
    Item * loadRecurXml(QDomElement rootXml, Item * rootLoading, QMap<QString, QString> *correspondances);
    void convertOldUUIDToNewItems(Item * rootLoading, QMap<QString, QString> * correspondances, Item *rootElem);

    void process(Item *item, QComboBox *c);
    void videCombo(QComboBox *c);
    void saveRightPanel(Item *wi);
    Item * getItemWithUUID(QString uid, Item *item);
    void listerTemplate();
    QStringList * listeTemplate;
    void refresh(Item * centerOn);

    bool verifierSiPasDeBoucle(Item *elem, Item *ref);
    bool isNotDependantOf(Item *item);
    QDate daysToRealDate(Item *item);
private:
    Item * selectedItem;
    MainWindow * theControlledWindow;
    QStringList * malisteuid;

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
    void cancelModification();
    void saveModification();
    void getDrop(QString s);
    void deleteItemListView(QListWidgetItem *wi);
    void setRDButton(int i);
};

#endif // CONTROLEUR_H
