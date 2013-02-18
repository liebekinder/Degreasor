#include "controleur.h"

#include "mainwindow.h"


Controleur::Controleur(MainWindow * theControlledWindow,QObject *parent) :
    QObject(parent)
{
    root_ = new Ensemble(true);
    selectedItem = root_;
    this->theControlledWindow = theControlledWindow;
    //root_ = new Ensemble("nom", QDate::currentDate(),"bla", NULL);
    //qDebug()<< Item::TwoDaysAfter;
}

Item * Controleur::getSelectedItem()
{
    return selectedItem;
}

void Controleur::setSelectedItem(Item * wi)
{
    selectedItem = wi;
    refreshRightPanel(wi);
    //methode d'affichage de la partie droite de l'ui
}

void Controleur::refreshRightPanel(Item * wi, bool b)
{
    //actualisation des combobox
    videCombo(theControlledWindow->cbb2);
    process(root_, theControlledWindow->cbb2);

    if(b){
        //nom
        theControlledWindow->le1->setText("");

        //choix de la date
        theControlledWindow->cb1->setChecked(true);
        //date
        theControlledWindow->de->setDate(QDate::currentDate());
        theControlledWindow->cbb1->setCurrentIndex(0);
        if(((Ensemble *)root_)->getNotreListe()->size() != 0)
        {
            theControlledWindow->cbb2->setCurrentIndex(0);
        }
        //description
        theControlledWindow->te->setText("");

        theControlledWindow->b1->setDisabled(true);
        theControlledWindow->b2->setDisabled(true);
    }
    else{
        //nom
        theControlledWindow->le1->setText(wi->getNom());

        //choix de la date
        if(wi->getChoixDate()) theControlledWindow->cb1->setChecked(true);
        else theControlledWindow->cb2->setChecked(true);
        //date
        theControlledWindow->de->setDate(wi->getDate());
        theControlledWindow->cbb1->setCurrentText(wi->getAssocie()->getDateRString(wi->getDateR()));
        if(((Ensemble *)root_)->getNotreListe()->size() != 0)
        {
            theControlledWindow->cbb2->setCurrentIndex(0);
        }
        //description
        theControlledWindow->te->setText(wi->getDescription());

        theControlledWindow->b1->setDisabled(false);
        theControlledWindow->b2->setDisabled(false);
    }

}

void Controleur::saveRightPanel(Item * wi)
{
    wi->setNom(theControlledWindow->le1->text());
    if(theControlledWindow->cb1->isChecked())
    {
        wi->setChoixDate(true);
        wi->setDate(theControlledWindow->de->date());
    }
    else
    {
        wi->setChoixDate(true);
        wi->setDateR(wi->getComboBoxFromText(theControlledWindow->cbb1->currentText()));
        QVariant v = theControlledWindow->cbb2->itemData(theControlledWindow->cbb2->currentIndex());
        //méthode de récupération de l'item via le quuid du qvariant
        qDebug()<<v.toString();
    }
    wi->setDescription(theControlledWindow->te->toPlainText());

    callRefreshWithoutMoveScreen();
}

void Controleur::videCombo(QComboBox * c){
    for(int i=c->count()-1; i>=0;--i){
        c->removeItem(i);
    }
}

void Controleur::process(Item * item, QComboBox * c)
{
    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(item->getType() == "liste") maListe =( (Liste *)item)->getNotreListe();
    if(item->getType() == "ensemble") maListe =( (Ensemble *)item)->getNotreListe();

    qDebug()<<"iterateur... done!";
    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        qDebug()<<"un tour!... done!";
        Item * currentItem = ((Item*)*it);
        qDebug()<<currentItem;
        qDebug()<<"cast!... done!";
        qDebug()<<currentItem->getType();

        if(currentItem->getType() == "tache")
        {
            qDebug()<<"tache ajout... done!";
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            qDebug()<<"listez/ensemble ajout... done!";
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
            process(currentItem, c);
            qDebug()<<"listez/ensemble ajout... done!";
        }
    }
}

/*void Controleur::parseAndAddAfter(Item * currentList, Item * elementPere ,Item * elementToAdd)
{
    Item * root;
    if(currentList->getType()=="ensemble") root = ((Ensemble *)currentList);
    else root = ((Liste *)currentList);


    QList<Item *>::iterator it;
    QList<Item *> * maListe = currentList->getType()=="ensemble" ? ((Ensemble *)root)->getNotreListe() :  ((Liste *)root)->getNotreListe() ;

    for(it= maListe->begin();it != maListe->end();++it)
    {

        Item * currentItem = ((Item*)*it);

        qDebug()<<"de  "+currentItem->getNom();
        if(currentItem==elementPere)
        {
            if(currentList->getType()=="ensemble") {
                elementToAdd->setParent(currentList);
                ((Ensemble *)currentList)->ajoutItem(elementToAdd);
                break;
            }
            else
            {
                elementToAdd->setParent(currentList);
                ((Liste *)currentList)->ajoutItem(elementToAdd);
                break;
            }
        }
        else
        {
            if(currentItem->getType()=="ensemble")
            {
                Controleur::parseAndAddAfter(currentItem, elementPere ,elementToAdd);
            }
            if(currentItem->getType()=="liste")
            {
                Controleur::parseAndAddAfter(currentItem, elementPere ,elementToAdd);
            }
        }

    }
}*/

void Controleur::addEnsembleApres()
{
    Item * yeah = new Ensemble("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté! Ensemble avant";
    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApres()
{
    Item * yeah = new Liste("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté!";
    theControlledWindow->refresh(yeah);
}

void Controleur::addTacheApres()
{
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté!";
    theControlledWindow->refresh(yeah);

}

void Controleur::addTacheALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addListeALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);;
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsembleALaSuiteDeTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"", test->getParent()); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    if(test->getParent()->getType()=="ensemble")
    {
        ((Ensemble*) test->getParent())->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test->getParent())->ajoutItem(yeah);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::cancelModification()
{
    refreshRightPanel(selectedItem);
}

void Controleur::saveModification()
{
    saveRightPanel(selectedItem);
}

void Controleur::addTacheApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addListeApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsembleApresTache(Item *test)
{
    qDebug()<<test->getNom();
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"", test); //on set le parent quand on le connais
    //((Ensemble*)root_)->ajoutItem(yeah);

    //rendre la liste visible
    test->setVisible(true);

    if(test->getType()=="ensemble")
    {
        ((Ensemble*) test)->ajoutItem(yeah);
    }
    else
    {
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    theControlledWindow->refresh(yeah);
}

void Controleur::addEnsemble()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addListe()
{
    qDebug()<<"ajout détecté!";
}

void Controleur::addTache()
{
    qDebug()<<"ajout détecté!";
}

Item * Controleur::getRoot()
{
    return root_;
}

void Controleur::callRefreshWithoutMoveScreen()
{
    theControlledWindow->callRefreshWithoutMoveScreen();
}

bool Controleur::saveToXml(QString path,Item * racine,bool templateItem)
{
    if(racine==NULL) racine = root_;
    //global save

    QDomDocument* xml = new QDomDocument();
    if(!templateItem)
    {


        QDomNode xmlNode = xml->createProcessingInstruction("xml","version\"1.0\" encoding=\"UTF-8\"");
        xml->insertBefore(xmlNode,xml->firstChild());

        QDomElement root = xml->createElement("root");
        xml->appendChild(root);
        parseToXml(racine,root,xml);
    }
    else
    {
        QDomNode xmlNode = xml->createProcessingInstruction("xml","version\"1.0\" encoding=\"UTF-8\"");
        xml->insertBefore(xmlNode,xml->firstChild());

        QDomElement root = xml->createElement("template");
        xml->appendChild(root);

        /////

        QDomElement item = creeXmlItem(racine,xml);

        QDomElement children= xml->createElement("children");

        parseToXml(racine, children, xml);

        item.appendChild(children);

        root.appendChild(item);
        /////

    }

    //save
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    xml->save(ts,2,QDomNode::EncodingFromTextStream);
    return true;
}

QDomElement Controleur::creeXmlItem(Item * itemPh,QDomDocument * xml)
{
    QDomElement item = xml->createElement("item");
    item.setAttribute("type",itemPh->getType());
    item.setAttribute("visible",itemPh->getVisible());
    item.setAttribute("choixDate",itemPh->getChoixDate());
    item.setAttribute("date",itemPh->getDate().toString(Qt::ISODate));
    item.setAttribute("dateR",int(itemPh->getDateR()));

    if(itemPh->getAssocie()!=NULL) item.setAttribute("itemAssocie",itemPh->getAssocie()->getUID().toString());
    item.setAttribute("UID",itemPh->getUID().toString());
    item.setAttribute("parent",itemPh->getParent()->getUID().toString());

    QDomElement name= xml->createElement("name");
    name.appendChild(xml->createTextNode(itemPh->getNom()));
    item.appendChild(name);

    QDomElement description= xml->createElement("description");
    description.appendChild(xml->createTextNode(itemPh->getDescription()));
    item.appendChild(description);

    QDomElement preds= xml->createElement("preconditions");

    QList<Item *>::iterator it;
    QList<Item *> * maListe = itemPh->getPreconditions();

    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        Item * currentItem = ((Item*)*it);
        QDomElement pred= xml->createElement("precondition");
        pred.appendChild(xml->createTextNode(currentItem->getUID().toString()));
        preds.appendChild(pred);
    }

    item.appendChild(preds);

    return item;
}

void Controleur::parseToXml(Item * item, QDomElement currentNode,QDomDocument * xml)
{
    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(item->getType() == "liste") maListe =( (Liste *)item)->getNotreListe();
    if(item->getType() == "ensemble") maListe =( (Ensemble *)item)->getNotreListe();

    qDebug()<<"iterateur... done!";
    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        qDebug()<<"un tour!... done!";
        Item * currentItem = ((Item*)*it);

        if(currentItem->getType() == "tache")
        {

            currentNode.appendChild(creeXmlItem(currentItem,xml));



        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            QDomElement item = creeXmlItem(currentItem,xml);

            QDomElement children= xml->createElement("children");

            parseToXml(currentItem, children, xml);

            item.appendChild(children);

            currentNode.appendChild(item);
        }
    }
}


