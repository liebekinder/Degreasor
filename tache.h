#ifndef TACHE_H
#define TACHE_H

#include <QObject>

class Tache : public Item
{
    Q_OBJECT
public:
    Tache(QObject *parent = 0);
    Tache(QString nom, QDate date, QString description, QObject *parent);

signals:
    
public slots:
    
};

#endif // TACHE_H
