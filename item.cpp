#include "item.h"

//construction
Item::Item(Item *conteneur, QObject *parent) :
    QObject(parent)
{
    nom_ = "Mon nouvel item";
    date_ = QDate::currentDate();
    dateR_ = Now;
    setParent(conteneur);
    choixDate_ = true;
    UID = QUuid::createUuid();
    itemAssocie_=NULL;
    precondition_ = new QList<Item * >();
    //qDebug()<<UID.toString();
}

Item::Item(bool root, QObject *parent) :
    QObject(parent)
{
    Q_UNUSED(root);
    //root = true; //enlever le warning
    nom_ = "Root";
    choixDate_ = true;
    date_ = QDate::currentDate();
    dateR_ = Now;
    UID = QUuid::createUuid();
    itemAssocie_=NULL;
    precondition_ = new QList<Item * >();
}

Item::Item(QString nom, QDate date, QString description, Item *conteneur, QObject *parent) :
    QObject(parent)
{
    visible = true;
    nom_ = nom;
    date_ = date;
    dateR_ = Now;
    description_ = description;
    setParent(conteneur);
    choixDate_ = true;
    UID = QUuid::createUuid();
    itemAssocie_=NULL;
    precondition_ = new QList<Item * >();
    //qDebug()<<UID.toString();
}

void Item::setType(QString t)
{
    //verification des types
    if(t != "ensemble" && t != "liste" && t != "tache"){
        qErrnoWarning(10, "le type crée n'existe pas!");
    }
    else{
        TYPE = t;
    }
}

void Item::setVisible(bool b)
{
    visible=b;
}

bool Item::getChoixDate()
{
    return choixDate_;
}

void Item::setChoixDate(bool b)
{
    choixDate_ = b;
}

void Item::setUID(QUuid i)
{
    UID = i;
}

QUuid Item::getUID()
{
    return UID;
}

void Item::getComboBox(QComboBox * c){
    c->addItem("Deux semaines avant");
    c->addItem("Une semaine avant");
    c->addItem("Deux jours avant");
    c->addItem("Un jour avant");
    c->addItem("En même temps");
    c->addItem("Un jour après");
    c->addItem("Deux jours après");
    c->addItem("Une semaine après");
    c->addItem("Deux semaines après");
}

Item::DateRelative Item::getComboBoxFromText(QString s)
{
    if(s == "Deux semaines avant") return TwoWeeksBefore;
    else if(s == "Une semaine avant") return OneWeekBefore;
    else if(s == "Deux jours avant") return TwoDaysBefore;
    else if(s == "Un jour avant") return OneDayBefore;
    else if(s == "En même temps") return Now;
    else if(s == "Un jour après") return OneDayAfter;
    else if(s == "Deux jours après") return TwoDaysAfter;
    else if(s == "Une semaine après") return OneWeekAfter;
    else if(s == "Deux semaines après") return TwoWeeksAfter;
    else return Now;
}

QString Item::getDateRString(Item::DateRelative d)
{
    QString retour;
    switch(d){
    case TwoWeeksBefore:
        retour = "Deux semaines avant";
        break;
    case OneWeekBefore:
        retour = "Une semaine avant";
        break;
    case TwoDaysBefore:
        retour = "Deux jours avant";
        break;
    case OneDayBefore:
        retour = "Un jour avant";
        break;
    case Now:
        retour = "En même temps";
        break;
    case OneDayAfter:
        retour = "Un jour après";
        break;
    case TwoDaysAfter:
        retour = "Deux jours après";
        break;
    case OneWeekAfter:
        retour = "Une semaine après";
        break;
    case TwoWeeksAfter:
        retour = "Deux semaines après";
        break;
    default:
        retour = "erreur";
        break;
    }
    return retour;
}

QList<Item *> * Item::getPreconditions()
{
    return precondition_;
}

void Item::setPreconditions(QList<Item *> * pred)
{
    precondition_ = pred;
}

bool Item::getVisible()
{
    return visible;
}

QString Item::getType()
{
    return TYPE;
}

QString Item::getNom()
{
    return nom_;
}

QDate Item::getDate()
{
    return date_;
}

Item::DateRelative Item::getDateR()
{
    return dateR_;
}

QString Item::getDescription()
{
    return description_;
}

QWidget *Item::getVue()
{
    return vue_;
}

Item *Item::getParent()
{
    return parent_;
}

void Item::setAssocie(Item *i)
{
    itemAssocie_ = i;
}

Item * Item::getAssocie()
{
    return itemAssocie_;
}

void Item::setNom(QString n)
{
    nom_ = n;
}

void Item::setDate(QDate d)
{
    date_ = d;
}

void Item::setDateR(Item::DateRelative r)
{
    dateR_ = r;
}

void Item::setDescription(QString i)
{
    description_ = i;
}

void Item::setVue(QWidget *v)
{
    vue_ = v;
}

void Item::setParent(Item *p)
{
    parent_ = p;
}
