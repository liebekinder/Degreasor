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
    malisteuid = new QStringList();
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

    theControlledWindow->dropListe->clear();
    malisteuid->clear();

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

        //on copie la ligne de preconditions dans le qlist widget, en 2 ligne dont une caché UID

        for(int i=0; i<wi->getPreconditions()->count(); ++i)
        {
            theControlledWindow->dropListe->addItem(new QListWidgetItem(wi->getPreconditions()->at(i)->getNom()));
            malisteuid->append(wi->getPreconditions()->at(i)->getUID().toString());
        }

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


    QList<Item *> * precond = new QList<Item *>();
    //on avance de 2 en 2, pour saisir à la fois le nom et le paramètre caché UID
    for(int i=0; i<malisteuid->count(); ++i){
        precond->append( getItemWithUUID(malisteuid->at(i), root_) );
    }
    qDebug()<<"precond->size()";
    qDebug()<<precond->size();
    wi->setPreconditions(precond);

    callRefreshWithoutMoveScreen();
}

Item * Controleur::getItemWithUUID(QString uid, Item * item)
{
    QUuid * id = new QUuid(uid);
    Item * trouve = NULL;

    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(item->getType() == "liste") maListe =( (Liste *)item)->getNotreListe();
    if(item->getType() == "ensemble") maListe =( (Ensemble *)item)->getNotreListe();

    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        Item * currentItem = ((Item*)*it);

        if(currentItem->getUID() == *id) trouve = currentItem;

        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            trouve = trouve == NULL ? getItemWithUUID(uid, currentItem): trouve;
        }

    }
    return trouve;
}

void Controleur::listerTemplate()
{
    listeTemplate = new QStringList();

    if( !(new QDir(QDir::currentPath() + "/templates"))->exists())
    {
        (new QDir(QDir::currentPath()))->mkdir("templates");
    }
    QDir * dir = new QDir(QDir::currentPath()+"/templates");
    QStringList list(dir->entryList(QDir::Files|QDir::NoDotAndDotDot));
    for(int i=0;i<list.size();++i){
        if((new QFileInfo(list.at(i)))->suffix() == "template"){
            listeTemplate->append((new QFileInfo(list.at(i)))->filePath());
        }
    }
    qDebug()<<listeTemplate->size();

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

    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        Item * currentItem = ((Item*)*it);

        if(currentItem->getType() == "tache")
        {
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
            process(currentItem, c);
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

void Controleur::getDrop(QString s)
{
    qDebug()<<"drop détecté et transmis!";
    theControlledWindow->dropListe->addItem(new QListWidgetItem(getItemWithUUID(s,root_)->getNom()));
    malisteuid->append(s);
    //theControlledWindow->dropListe->addItem(new QListWidgetItem(s));
    //qDebug()<<s;
    //qDebug()<<theControlledWindow->dropListe->count();
    //theControlledWindow->dropListe->itemAt(theControlledWindow->dropListe->count(),1)->setHidden(true);
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

void Controleur::setRoot(Item * root)
{
    root_=root;
}

void Controleur::callRefreshWithoutMoveScreen()
{
    theControlledWindow->callRefreshWithoutMoveScreen();
}

bool Controleur::saveToXml(QString path,Item * racine,Item * deleteItem ,bool templateItem)
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
        parseToXml(racine,root,xml,deleteItem);
    }
    else
    {
        QDomNode xmlNode = xml->createProcessingInstruction("xml","version\"1.0\" encoding=\"UTF-8\"");
        xml->insertBefore(xmlNode,xml->firstChild());

        QDomElement root = xml->createElement("root");
        xml->appendChild(root);

        /////

        QDomElement item = creeXmlItem(racine,xml);

        QDomElement children= xml->createElement("children");

        parseToXml(racine, children, xml,deleteItem);

        item.appendChild(children);

        root.appendChild(item);
        /////

    }

    //save
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) return false;
    QTextStream ts(&file);
    ts.setCodec("UTF-8");
    xml->save(ts,2,QDomNode::EncodingFromTextStream);
    return true;
}

Item * Controleur::chargerXml(QString path,bool templateP)
{
    QFile file(path);

    if(file.open(QFile::ReadOnly|QFile::Text)){
        if(!templateP)
        {
            QDomDocument xml;
            xml.setContent(&file,false);

            Ensemble * rootLoading = new Ensemble(true);

            QMap<QString,QString> * correspondances = new QMap<QString,QString>();

            QDomElement rootXml = xml.documentElement();
            rootXml=rootXml.firstChildElement();
            //on a dans quiz la balise <root></root>
            while(!rootXml.isNull())
            {
                //qDebug()<<"@@@@@@"+rootXml.tagName();
                rootLoading->ajoutItem(loadRecurXml(rootXml,rootLoading,correspondances));
                rootXml=rootXml.nextSiblingElement();
            }

            //Gestion des préconditions...
            convertOldUUIDToNewItems(rootLoading,correspondances,rootLoading);

            qDebug()<<"Fin load";
            return rootLoading;
        }
        else
        {
            QDomDocument xml;
            xml.setContent(&file,false);

            Ensemble * rootLoading = new Ensemble(true);

            QMap<QString,QString> * correspondances = new QMap<QString,QString>();

            QDomElement rootXml = xml.documentElement();
            rootXml=rootXml.firstChildElement();
            //on a dans quiz la balise <root></root>
            while(!rootXml.isNull())
            {
                //qDebug()<<"@@@@@@"+rootXml.tagName();
                rootLoading->ajoutItem(loadRecurXml(rootXml,rootLoading,correspondances));
                rootXml=rootXml.nextSiblingElement();
            }

            //Gestion des préconditions...
            convertOldUUIDToNewItems(rootLoading,correspondances,rootLoading);

            qDebug()<<"Fin load";
            return rootLoading->getNotreListe()->at(0);
        }

    }
    qDebug()<<"Erreur lecture fichier";
    return NULL;

}

void Controleur::convertOldUUIDToNewItems(Item * rootLoading,QMap<QString, QString> * correspondances, Item * rootElem)
{
    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(rootLoading->getType() == "liste") maListe =( (Liste *)rootLoading)->getNotreListe();
    if(rootLoading->getType() == "ensemble") maListe =( (Ensemble *)rootLoading)->getNotreListe();

    qDebug()<<"iterateur... done!";
    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        qDebug()<<"un tour!... done!";
        Item * currentItem = ((Item*)*it);

        if(currentItem->getType() == "tache")
        {
            //conversion
            qDebug()<<currentItem->getNom();
            QList<QString> * OLDUUIDList = currentItem->getPrecondSS();
            QList<Item * > * preconditionsWithNewUUID = new QList<Item * >();
            QList<QString>::iterator itUUID;
            qDebug()<<currentItem->getNom();
            for(itUUID = OLDUUIDList->begin(); itUUID != OLDUUIDList->end(); ++itUUID)
            {
                QString currentOLDUUID = ((QString)*itUUID);
                qDebug()<<currentOLDUUID;
                if((correspondances->contains(currentOLDUUID)))
                {
                    qDebug()<<*correspondances->find(currentOLDUUID);
                    preconditionsWithNewUUID->append(getItemWithUUID(((QString)*correspondances->find(currentOLDUUID)),rootElem));
                }

            }
            qDebug()<<currentItem->getNom();
            currentItem->setPreconditions(preconditionsWithNewUUID);
        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            convertOldUUIDToNewItems(currentItem, correspondances,rootElem);
        }
    }

}


Item * Controleur::loadRecurXml(QDomElement rootXml,Item * rootLoading,QMap<QString,QString> * correspondances)
{
    Item * newItem;
    if(rootXml.tagName() == "item"){
        //qDebug()<<rootXml.attribute(QString("type"));

        if(rootXml.attribute(QString("type"))=="tache")
        {
            newItem = new Tache("",QDate::fromString(rootXml.attribute(QString("date"))),rootXml.attribute(QString("description")),rootLoading);
        }
        else if(rootXml.attribute(QString("type"))=="liste")
        {
            newItem = new Liste("",QDate::fromString(rootXml.attribute(QString("date"))),rootXml.attribute(QString("description")),rootLoading);
        }
        else
        {
            newItem = new Ensemble("",QDate::fromString(rootXml.attribute(QString("date"))),rootXml.attribute(QString("description")),rootLoading);
        }

        newItem->setVisible(rootXml.attribute(QString("visible"))=="0"?false:true);
        newItem->setType(rootXml.attribute(QString("type")));
        //newItem->setUID(QUuid(rootXml.attribute(QString("UID"))));
        //nouvel UUID, ancien UUID
            correspondances->insert(rootXml.attribute(QString("UID")),newItem->getUID().toString());
        newItem->setChoixDate(rootXml.attribute(QString("choixDate"))=="0"?false:true);
        newItem->setDateR((Item::DateRelative)rootXml.attribute(QString("dateR")).toInt());

        QDomElement nomEtChildren = rootXml.firstChildElement();
        while(!nomEtChildren.isNull())
        {
            if(nomEtChildren.tagName()=="name")
            {
                qDebug()<<nomEtChildren.text();
                newItem->setNom(nomEtChildren.text());
            }
            else if(nomEtChildren.tagName()=="description")
            {
                qDebug()<<nomEtChildren.text();
                newItem->setDescription(nomEtChildren.text());
            }
            else if(nomEtChildren.tagName()=="children")
            {
                qDebug()<<"traitement des enfants";
                QDomElement childish = nomEtChildren.firstChildElement();
                while(!childish.isNull())
                {
                    if(newItem->getType()=="ensemble")
                    {
                        ((Ensemble*)newItem)->ajoutItem(loadRecurXml(childish,newItem,correspondances));
                    }
                    else
                    {
                        ((Liste*)newItem)->ajoutItem(loadRecurXml(childish,newItem,correspondances));
                    }
                    childish=childish.nextSiblingElement();
                }
            }
            else if(nomEtChildren.tagName()=="preconditions")
            {
                qDebug()<<"preconditions";
                QList<QString>* predSS = new QList<QString>();
                QDomElement pred = nomEtChildren.firstChildElement();
                while(!pred.isNull())
                {
                    if(pred.tagName()=="precondition")
                    {
                        //là ancien UUID !
                        predSS->append(QString(pred.text()));
                    }
                    pred=pred.nextSiblingElement();
                }
                newItem->setPrecondSS(predSS);
            }
            else
            {
                qDebug()<<"What the fuck himself !"+nomEtChildren.tagName();
            }
            nomEtChildren=nomEtChildren.nextSiblingElement();
        }

        //buildItemViaXml(rootXml.firstChildElement(),newItem);
    }

    return newItem;
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

void Controleur::parseToXml(Item * item, QDomElement currentNode,QDomDocument * xml, Item * deleteItem)
{
    QList<Item *>::iterator it;
    QList<Item *> * maListe;
    if(item->getType() == "liste") maListe =( (Liste *)item)->getNotreListe();
    if(item->getType() == "ensemble") maListe =( (Ensemble *)item)->getNotreListe();

    qDebug()<<"iterateur... done!";
    for(it = maListe->begin(); it != maListe->end(); ++it)
    {
        qDebug()<<"un tour!... done11!";
        Item * currentItem = ((Item*)*it);
        qDebug()<<"un tour!... done12!";
        QString UUIDDEl = deleteItem!=NULL?deleteItem->getUID().toString():"Prout";
        if(deleteItem!=NULL) qDebug()<<"sqfdghjkhgfsdghjkhgfdfgh"+UUIDDEl;
        if(currentItem->getUID().toString()!=UUIDDEl)
        {
            if(currentItem->getType() == "tache")
            {

                currentNode.appendChild(creeXmlItem(currentItem,xml));



            }
            if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
            {
                QDomElement item = creeXmlItem(currentItem,xml);

                QDomElement children= xml->createElement("children");

                parseToXml(currentItem, children, xml,deleteItem);

                item.appendChild(children);

                currentNode.appendChild(item);
            }
        }


    }
}


