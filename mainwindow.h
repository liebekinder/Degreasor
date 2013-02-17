#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMenu>
#include <Qlabel>
#include <QDate>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QScrollArea>

#include "mywidget.h"
#include "controleur.h"
#include "widget.h"
#include "affichage.h"
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    MainWindow(bool b, QWidget *parent = 0);
    void refresh();
    ~MainWindow();
    
private:

    Affichage * affichage;
    QStackedWidget *stackedWidget;
    Controleur * controler;
    QWidget * central;
    QVBoxLayout * centralL;
    QWidget * upperPane;
    QLabel * upperPaneT;
    QFrame * line;
    QFrame * line2;
    QVBoxLayout * upperPaneL;
    QWidget * lowerPane;
    QHBoxLayout * lowerPaneL;
    myWidget * vue;
    QVBoxLayout * vueL;
    QWidget * info;
    QVBoxLayout * infoL;
    QLabel * infoLabel;

    QWidget *setInfoPanel(bool b);

    QHBoxLayout * hb1;
    QHBoxLayout * hb2;
    QHBoxLayout * hb3;
    QHBoxLayout * hb4;
    QVBoxLayout * vb1;
    QGroupBox * gb1;
    QLabel * lb1;
    QLabel * lb2;
    QLabel * lb3;
    QLabel * lb4;
    QLabel * lb5;
    QLabel * lb6;
    QLineEdit * le1;
    QRadioButton * cb1;
    QRadioButton * cb2;
    QDateEdit * de;
    QComboBox * cbb1;
    QComboBox * cbb2;
    QTextEdit * te;
    QWidget * widg;
    QPushButton * b1;
    QPushButton * b2;



};

#endif // MAINWINDOW_H
