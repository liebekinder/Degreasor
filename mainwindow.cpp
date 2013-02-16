#include "mainwindow.h"

MainWindow::MainWindow(bool b, QWidget * parent) :
    QMainWindow(parent){
    qDebug()<<"mode console "<<b;

    Controleur * c = new Controleur();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(920,480);
    setWindowTitle(tr("Degreasor!"));

    controler = new Controleur();

    central = new QWidget();
    centralL = new QVBoxLayout();

    upperPane = new QWidget();
    upperPaneL = new QVBoxLayout();
        upperPaneT = new QLabel();
        upperPaneL->addWidget(upperPaneT);
    upperPane->setLayout(upperPaneL);

    line = new QFrame();
    line->setFrameShape(QFrame::HLine);

    lowerPane = new QWidget();

        centralL->addWidget(upperPane,1);
        centralL->addWidget(line,1);
        lowerPaneL = new QHBoxLayout();

        vue = new myWidget(controler);
            vueL = new QVBoxLayout();
                QLabel * empty = new QLabel("- empty list -");
                vueL->addWidget(empty);
                vueL->setAlignment(Qt::AlignCenter);
            vue->setLayout(vueL);

            line2 = new QFrame();
            line2->setFrameShape(QFrame::VLine);

            info = setInfoPanel(true);

            lowerPaneL->addWidget(vue,7);
            lowerPaneL->addWidget(line2);
            lowerPaneL->addWidget(info,3);

        lowerPane->setLayout(lowerPaneL);

        centralL->addWidget(lowerPane,20);
    central->setLayout(centralL);

    setCentralWidget(central);

    //configuration

    upperPaneT->setText(QDate::currentDate().toString());
    upperPaneL->setAlignment(Qt::AlignHCenter);


    //actions


}

QWidget *MainWindow::setInfoPanel(bool b){
    info = new QWidget();
    infoL = new QVBoxLayout();

    if(b){
        hb1 = new QHBoxLayout();
        hb2 = new QHBoxLayout();
        hb3 = new QHBoxLayout();
        hb4 = new QHBoxLayout();

        vb1 = new QVBoxLayout();

        gb1 = new QGroupBox("Date: ");

        lb1 = new QLabel("Nom de la tâche: ");
        lb2 = new QLabel("L'évènement a lieu le ");
        lb3 = new QLabel("ou");
        lb4 = new QLabel("la tâche ");
        lb5 = new QLabel("Commentaires sur la tâche: ");
        lb6 = new QLabel("préconditions (tâche devant être accomplies avant la tâche courante): ");

        le1 = new QLineEdit();

        cb1 = new QRadioButton();
        cb2 = new QRadioButton();

        de = new QDateEdit();

        cbb1 = new QComboBox();
        cbb2 = new QComboBox();

        te = new QTextEdit();
        widg = new QWidget();
        widg->setMinimumHeight(75);

        b1 = new QPushButton("Annuler");
        b2 = new QPushButton("Sauvegarder");

            hb1->addWidget(lb1);
            hb1->addWidget(le1);
        infoL->addLayout(hb1);

                hb2->addWidget(cb1,1);
                hb2->addWidget(lb2,5);
                hb2->addWidget(de,5);
            vb1->addLayout(hb2);
            vb1->addWidget(lb3);
                hb3->addWidget(cb2,1);
                hb3->addWidget(cbb1,5);
                hb3->addWidget(lb4,2);
                hb3->addWidget(cbb2,5);
            vb1->addLayout(hb3);
            gb1->setLayout(vb1);
        infoL->addWidget(gb1);

        infoL->addWidget(lb5);
        infoL->addWidget(te);
        infoL->addWidget(lb6);
        infoL->addWidget(widg);

            hb4->addWidget(b1);
            hb4->addWidget(b2);
        infoL->addLayout(hb4,2);
    }


    info->setLayout(infoL);
    return info;
}

MainWindow::~MainWindow()
{
}
