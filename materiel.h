#ifndef MATERIEL_H
#define MATERIEL_H
#include "maintenance.h"
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>
#include<QSystemTrayIcon>

class Materiel
{   QString type,etat,maint;
    int id;
    QDate dateachat;

public:
    Materiel();
    Materiel (int,QString,QString,QDate,QString);
    int get_id();
    QString get_type();
    QString get_etat();
    QString get_maint();
    QDate get_dateachat();
    bool ajouter();
    //bool modifier();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher2();
    bool supprimer(int);
    QSqlQueryModel *cherchermateriel(int id);

};

#endif // MATERIEL_H
