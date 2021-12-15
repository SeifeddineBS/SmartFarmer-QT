#ifndef EVENEMENTS_H
#define EVENEMENTS_H
#include <QString>
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QComboBox>
#include <QDate>


class Evenements
{
public:
    Evenements();
    Evenements(QString,QString,QString,QString,QDate);
    QString get_id();
    QString get_nom();
    QString get_type();
    QString get_lieu();
    QDate get_datee();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * trier();
    QSqlQueryModel * rechercher (QString ev );
private:
    QString id,nom,type,lieu;
    QDate datee;
};

#endif // EVENEMENTS_H
