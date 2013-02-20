#-------------------------------------------------
#
# Project created by QtCreator 2013-01-29T10:12:24
#
#-------------------------------------------------

QT       += core gui\
    xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Degreasor
TEMPLATE = app

INCLUDEPATH += . \
    Controler \
    View \
    Core \
    View/MainWindow \
    View/Widget


SOURCES += main.cpp\
        View/MainWindow/mainwindow.cpp \
    View/MainWindow/mywidget.cpp \
    Core/item.cpp \
    Core/ensemble.cpp \
    Core/liste.cpp \
    Core/tache.cpp \
    View/Widget/widget.cpp \
    View/Widget/entete.cpp \
    View/MainWindow/droparea.cpp \
    View/Widget/dragzone.cpp \
    Controler/controleur.cpp \
    Controler/affichage.cpp

HEADERS  += View/MainWindow/mainwindow.h \
    View/MainWindow/mywidget.h \
    Core/item.h \
    Core/ensemble.h \
    Core/liste.h \
    Core/tache.h \
    View/Widget/widget.h \
    View/Widget/entete.h \
    View/MainWindow/droparea.h \
    View/Widget/dragzone.h \
    Controler/controleur.h \
    Controler/affichage.h

FORMS    +=

OTHER_FILES += \
    FileError.txt

RESOURCES += \
    Degreasor_ressources.qrc
