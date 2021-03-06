#include "controleur.h"
#include "mainwindow.h"
#include <QMessageBox>
#include "affichage.h"


Controleur::Controleur(MainWindow * theControlledWindow,QObject *parent) :
    QObject(parent)
{
    widgetHeight = 50;
    loadImages();

    root_ = new Ensemble(true);
    selectedItem = root_;
    this->theControlledWindow = theControlledWindow;
    this->affichage =new Affichage();
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
        theControlledWindow->le1->setDisabled(true);
        theControlledWindow->te->setDisabled(true);
        theControlledWindow->dropListe->setDisabled(true);
        theControlledWindow->widg->setDisabled(true);
        theControlledWindow->le1->setText("");

        //choix de la date
        theControlledWindow->cb1->setDisabled(true);
        theControlledWindow->cb2->setDisabled(true);
        //date
        theControlledWindow->de->setDisabled(true);
        theControlledWindow->de->setDate(QDate::currentDate());
        theControlledWindow->cbb1->setCurrentIndex(0);
        theControlledWindow->cbb1->setDisabled(true);
        if(((Ensemble *)root_)->getNotreListe()->size() != 0)
        {
            theControlledWindow->cbb2->setCurrentIndex(0);
        }
        theControlledWindow->cbb2->setDisabled(true);
        //description
        theControlledWindow->te->setText("");

        theControlledWindow->b1->setDisabled(true);
        theControlledWindow->b2->setDisabled(true);
    }
    else{
        theControlledWindow->le1->setDisabled(false);
        theControlledWindow->te->setDisabled(false);
        theControlledWindow->dropListe->setDisabled(false);
        theControlledWindow->widg->setDisabled(false);
        //choix de la date
        theControlledWindow->cb1->setDisabled(false);
        theControlledWindow->cb2->setDisabled(false);
        if(wi->getChoixDate()) theControlledWindow->cb1->setChecked(true);
        else theControlledWindow->cb2->setChecked(true);
        //date
        theControlledWindow->de->setDisabled(false);

        if(wi->getDate().toString(Qt::ISODate)!="")
        {
            theControlledWindow->de->setDate(wi->getDate());
        }
        else
        {
            theControlledWindow->de->setDate(QDate::currentDate());
        }

        qDebug()<<"iodshdiofsdiohhpifdhihidfpodsf"+wi->getDate().toString(Qt::ISODate);




        theControlledWindow->cbb1->setDisabled(false);
        theControlledWindow->cbb2->setDisabled(false);
        theControlledWindow->cbb1->setCurrentText(wi->getAssocie()->getDateRString(wi->getDateR()));
        if(((Ensemble *)root_)->getNotreListe()->size() != 0)
        {
            theControlledWindow->cbb2->setCurrentIndex(0);

        }
        if(wi->getAssocie()!=NULL)
        {
            for(int i= 0; i <theControlledWindow->cbb2->count();i++)
            {
                int j = theControlledWindow->cbb2->findData(QVariant(wi->getAssocie()->getUID().toString()));
                if(j>0) theControlledWindow->cbb2->setCurrentIndex(j);

            }

        }

        //description
        theControlledWindow->te->setText(wi->getDescription());

        //on copie la ligne de preconditions dans le qlist widget, en 2 ligne dont une caché UID

        for(int i=0; i<wi->getPreconditions()->count(); ++i)
        {
            theControlledWindow->dropListe->addItem(new QListWidgetItem(wi->getPreconditions()->at(i)->getNom()));
            malisteuid->append(wi->getPreconditions()->at(i)->getUID().toString());

        }

        //nom
        theControlledWindow->le1->setText(wi->getNom());

        theControlledWindow->le1->setFocus();
        theControlledWindow->le1->deselect();
        theControlledWindow->b2->setDefault(true);
        theControlledWindow->b1->setDisabled(false);
        theControlledWindow->b2->setDisabled(false);
    }
    callRefreshWithoutMoveScreen();

}

void Controleur::saveRightPanel(Item * wi)
{
    wi->setNom(theControlledWindow->le1->text());


    //######################################################


    qDebug()<< theControlledWindow->de->date().toString();
    qDebug()<< wi->getDate().toString();
    if(theControlledWindow->cb1->isChecked())
    {
        wi->setChoixDate(true);

    }
    else
    {
        QVariant v = theControlledWindow->cbb2->itemData(theControlledWindow->cbb2->currentIndex());
        wi->setAssocie(getItemWithUUID(v.toString(),root_));
        qDebug()<<"iofhfghigfsihgfhogfshiofsgRAMMSTEIN!"+wi->getAssocie()->getNom();
        //wi->setDate(daysToRealDate(wi));
        wi->setChoixDate(false);
       // qDebug()<<"qsfdsdffdqfqfdd"+wi->getDate().toString(Qt::ISODate);

         //qDebug()<<"qsfiodsfddf@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@qfusqfyqfs"+date.toString();

        //wi->setDateR((Item::DateRelative));
        wi->setDateR(wi->getComboBoxFromText(theControlledWindow->cbb1->currentText()));

        qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
        QDate date = daysToRealDate(wi);
        qDebug()<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&";
       theControlledWindow->de->setDate(date);

        //méthode de récupération de l'item via le quuid du qvariant

        //QMessageBox::warning(this->theControlledWindow->vue,"1",wi->getAssocie()->getNom());
        //qDebug()<<v.toString();
    }

    wi->setDate(theControlledWindow->de->date());
    qDebug()<< theControlledWindow->de->date().toString();
    qDebug()<< wi->getDate().toString();

    //#######################################################

    wi->setDescription(theControlledWindow->te->toPlainText());


    QList<Item *> * precond = new QList<Item *>();
    //on avance de 2 en 2, pour saisir à la fois le nom et le paramètre caché UID
    for(int i=0; i<malisteuid->count(); ++i){
        precond->append( getItemWithUUID(malisteuid->at(i), root_) );
    }
    qDebug()<<"precond->size()";
    qDebug()<<precond->size();
    wi->setPreconditions(precond);

    refreshRightPanel(wi);
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

void Controleur::refresh(Item *centerOn)
{
    saveToXml("main.xml",getRoot());
    theControlledWindow->refresh1(centerOn);
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
            if(isNotDependantOf(currentItem))
            {
                c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
            }
            else
            {
                //c->addItem("NULL",QVariant(NULL));
            }

        }
        if(currentItem->getType()=="ensemble" || currentItem->getType() == "liste" )
        {
            if(isNotDependantOf(currentItem))
            {
                c->addItem(currentItem->getNom(),QVariant(currentItem->getUID().toString()));
            }
            else
            {
                //c->addItem("NULL",QVariant(NULL));
            }
            process(currentItem, c);
        }
    }
}

bool Controleur::isNotDependantOf(Item * item)
{
    bool retour = item!=this->selectedItem;
    if(item->getAssocie()!=NULL)
    {
        Item * currentItem =item->getAssocie();
        retour = currentItem!=this->selectedItem && isNotDependantOf(currentItem);

        //QMessageBox::warning(this->theControlledWindow->vue,item->getNom(),item->getNom());

    }
    return retour;
}

QDate Controleur::daysToRealDate(Item * item)
{

    if(item->getChoixDate() || item->getAssocie()==NULL)
    {
        qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+item->getNom();
        return item->getDate().isNull()?QDate::currentDate():item->getDate();
    }
    QDate retour = daysToRealDate(item->getAssocie());
    qDebug()<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"+retour.toString(Qt::ISODate);
    //QMessageBox::warning(this->theControlledWindow->vue,item->getNom(),QString::number(int(item->getDateR())));
    retour = retour.addDays(int(item->getDateR()));
    //QMessageBox::warning(this->theControlledWindow->vue,item->getNom(),retour.toString(Qt::ISODate));
    return retour;
}

int Controleur::getWidgetHeight()
{
    return widgetHeight;
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
    Item * yeah = new Ensemble("Default_Ensemble",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté! Ensemble avant";
    this->refresh(yeah);
}

void Controleur::addListeApres()
{
    Item * yeah = new Liste("Default_Liste",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté!";
    this->refresh(yeah);
}

void Controleur::addTacheApres()
{
    Item * yeah = new Tache("Default_Tache",QDate::currentDate(),"",root_);
    ((Ensemble *)root_)->ajoutItem(yeah);
    this->setSelectedItem(yeah);
    qDebug()<<"ajout détecté!";
    this->refresh(yeah);

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
        ((Liste*) test->getParent())->ajoutItem(yeah,test);
        qDebug()<<"test->getNom()uiefuufeuohfuofhuofzeohifehiofeoihsdfhifdshiihfdhidfsuohfdhuo";
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    this->refresh(yeah);
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
        ((Liste*) test->getParent())->ajoutItem(yeah,test);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);;
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    this->refresh(yeah);
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
        ((Liste*) test->getParent())->ajoutItem(yeah,test);
    }
    //Controleur::parseAndAddAfter(root_, test ,yeah);
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    this->refresh(yeah);
}

void Controleur::cancelModification()
{
    refreshRightPanel(selectedItem);
}

void Controleur::saveModification()
{
    saveRightPanel(selectedItem);
}

void Controleur::deleteItemListView(QListWidgetItem * wi){

    qDebug()<<"lllllllllllllllllllllllllllllllllllllll";
    qDebug()<<theControlledWindow->dropListe->count();
    int i =0;
    bool trouve = false;
    while (!trouve && i < theControlledWindow->dropListe->count()){
        if(theControlledWindow->dropListe->item(i)->text() == wi->text()) trouve = true;
        ++i;
    }
    delete (theControlledWindow->dropListe->item(i-1));
    malisteuid->removeAt(i-1);
    qDebug()<<"lllllllllllllllllllllllllllllllllllllll";
    qDebug()<<theControlledWindow->dropListe->count();
    qDebug()<<i-1;

    //theControlledWindow->dropListe->
}

void Controleur::setRDButton(int i)
{
    Q_UNUSED(i);
    this->theControlledWindow->cb2->setChecked(true);
}

void Controleur::getDrop(QString s)
{
    qDebug()<<"drop détecté et transmis!";
    Item * corr = getItemWithUUID(s,root_);

    if((this->selectedItem->getUID().toString()!=s) && verifierSiPasDeBoucle(corr,this->selectedItem) && !malisteuid->contains(s))
    {
        theControlledWindow->dropListe->addItem(new QListWidgetItem(corr->getNom()));
        malisteuid->append(s);
    }
    else
    {
        QMessageBox::warning(this->theControlledWindow->vue,"Hop hop hop !","Vous essayez de créer un défaut dans le continum de l'espace temps");
    }

    //theControlledWindow->dropListe->addItem(new QListWidgetItem(s));
    //qDebug()<<s;
    //qDebug()<<theControlledWindow->dropListe->count();
    //theControlledWindow->dropListe->itemAt(theControlledWindow->dropListe->count(),1)->setHidden(true);
}

bool Controleur::verifierSiPasDeBoucle(Item * elem, Item * ref)
{


    QList<Item *>::iterator it;
    QList<Item *> * maListe = elem->getPreconditions();
    //if(elem->getType() == "liste") maListe =((Liste *)elem)->getPreconditions();
    //if(elem->getType() == "ensemble") maListe =((Ensemble *)elem)->getPreconditions();

    bool retour = elem!=ref;

    if(!maListe->empty())
    {
        //Item * testI = ((Item*)*(maListe->begin()));
        //QMessageBox::warning(this->theControlledWindow->vue,"1","2");
        for(it = maListe->begin(); it != maListe->end(); ++it)
        {
            Item * currentItem = ((Item*)*it);
            if(currentItem==ref) retour = false;
            retour = retour && verifierSiPasDeBoucle(currentItem, ref);


        }
    }


    return retour;
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
        qDebug()<<"dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddtest->getNom()";
        ((Liste*) test)->ajoutItem(yeah);
    }
    qDebug()<<"test->getNom()";
    this->setSelectedItem(yeah);

    this->refresh(yeah);
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

    this->refresh(yeah);
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

    this->refresh(yeah);
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

Affichage *Controleur::getAffichage()
{
    return this->affichage;
}

void Controleur::setRoot(Item * root)
{
    root_=root;
}

void Controleur::callRefreshWithoutMoveScreen(bool save)
{
    if(save) saveToXml("main.xml",getRoot());
    theControlledWindow->callRefreshWithoutMoveScreen1();
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

        if(true)//currentItem->getType() == "tache")
        {
            //conversion
            qDebug()<<currentItem->getNom();
            QList<QString> * OLDUUIDList = currentItem->getPrecondSS();
            QList<Item * > * preconditionsWithNewUUID = new QList<Item * >();
            QList<QString>::iterator itUUID;
            qDebug()<<currentItem->getNom();

            if(currentItem->associeUUID != "" && currentItem->associeUUID != NULL)
            {
                if((correspondances->contains(currentItem->associeUUID)))
                {
                    //qDebug()<<*correspondances->find(currentItem->associeUUID);
                    currentItem->setAssocie(getItemWithUUID(((QString)*correspondances->find(currentItem->associeUUID)),rootElem));
                    qDebug() <<"diohofdsohifdshiofsdhiihofdsiohdfshiofdshiihdfsihhifdsiohdfs+"+currentItem->getNom()+"   djjdjdjjd  "+currentItem->getAssocie()->getNom();
                }
            }

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
            newItem = new Tache("",QDate::fromString(rootXml.attribute(QString("date")),Qt::ISODate),rootXml.attribute(QString("description")),rootLoading);
            ((Tache*)newItem)->setPercentage(rootXml.attribute(QString("percent")).toInt());
        }
        else if(rootXml.attribute(QString("type"))=="liste")
        {
            newItem = new Liste("",QDate::fromString(rootXml.attribute(QString("date")),Qt::ISODate),rootXml.attribute(QString("description")),rootLoading);
        }
        else
        {
            newItem = new Ensemble("",QDate::fromString(rootXml.attribute(QString("date")),Qt::ISODate),rootXml.attribute(QString("description")),rootLoading);
        }

        //newItem->setDate();
        //qDebug()<<"fdioqiohhioqfdiohdfhiohidqfqf@@@";
        //qDebug()<<rootXml.attribute(QString("date"));
        //qDebug() <<QDate::fromString(rootXml.attribute(QString("date")),Qt::ISODate);

        newItem->associeUUID = rootXml.attribute(QString("associe"));

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
    item.setAttribute("date",QString(itemPh->getDate().toString(Qt::ISODate)));

    item.setAttribute("dateR",int(itemPh->getDateR()));
    if(itemPh->getAssocie()!=NULL) item.setAttribute("associe",itemPh->getAssocie()->getUID().toString());

    if(itemPh->getAssocie()!=NULL) item.setAttribute("itemAssocie",itemPh->getAssocie()->getUID().toString());
    item.setAttribute("UID",itemPh->getUID().toString());
    item.setAttribute("parent",itemPh->getParent()->getUID().toString());
    if(itemPh->getType()=="tache") item.setAttribute("percent",QString::number((((Tache *)itemPh)->getPercentage())));

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


QPixmap Controleur::getPixmapForDeselectedTask()
{
    return pixmapForDeselectedTask;
}

QPixmap Controleur::getPixmapForSelectedTask()
{
    return pixmapForSelectedTask;
}

QPixmap Controleur::getPixmapForDeselectedTaskValidated()
{
    return pixmapForDeselectedTaskValidated;
}

QPixmap Controleur::getPixmapForSelectedTaskValidated()
{
    return pixmapForSelectedTaskValidated;
}

QPixmap Controleur::getPixmapForDeselectedList()
{
    return pixmapForDeselectedList;
}


QPixmap Controleur::getPixmapForSelectedList()
{
    return pixmapForSelectedList;
}

QPixmap Controleur::getPixmapMain()
{
    return pixmapMain;
}
QPixmap Controleur::getPixmapPlusBlanc()
{
    return pixmapPlusBlanc;
}
QPixmap Controleur::getPixmapPlusNoir()
{
    return pixmapPlusNoir;
}
QPixmap Controleur::getPixmapMoinsBlanc()
{
    return pixmapMoinsBlanc;
}
QPixmap Controleur::getPixmapMoinsNoir()
{
    return pixmapMoinsNoir;
}



void Controleur::loadImages()
{
    pixmapForDeselectedTask = resize(QPixmap(":/images/fondCourantElemDeselect.png"),widgetHeight/308.);
    pixmapForSelectedTask = resize(QPixmap(":/images/fondCourantElemDeselectS.png"),widgetHeight/308.);
    pixmapForDeselectedTaskValidated = resize(QPixmap(":/images/fondCourantElemSelect.png"),widgetHeight/308.);
    pixmapForSelectedTaskValidated = resize(QPixmap(":/images/fondCourantElemSelectS.png"),widgetHeight/308.);

    pixmapForSelectedList = resize(QPixmap(":/images/fondCourantListeS.png"),widgetHeight/308.);
    pixmapForDeselectedList = resize(QPixmap(":/images/fondCourantListe.png"),widgetHeight/308.);

    pixmapMain = resize(QPixmap(":/images/grabIcon.png"),widgetHeight/500.);

    pixmapPlusBlanc = resize(QPixmap(":/images/Plus.png"),widgetHeight/500.);
    pixmapPlusNoir = resize(QPixmap(":/images/PlusS.png"),widgetHeight/500.);
    pixmapMoinsBlanc = resize(QPixmap(":/images/Moins.png"),widgetHeight/500.);
    pixmapMoinsNoir = resize(QPixmap(":/images/MoinsS.png"),widgetHeight/500.);


}

QPixmap Controleur::resize(QPixmap px, double scale)
{
    return px.scaledToHeight(px.size().height()*scale,Qt::SmoothTransformation);
}

