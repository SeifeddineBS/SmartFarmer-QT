#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>

class Employe
{
public:
    Employe();
    Employe(QString,QString,QString,QString,int,QString);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_fonction();
    int get_salaire();
    QString get_mail();



    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher_livreur();
    QSqlQueryModel * afficher_vet();

    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * rechercher(QString);
    QSqlQueryModel * triemploye();
    QSqlQueryModel * afficher1();


private:
    QString nom,prenom,fonction,id,mail;
    int salaire;
};

#endif // EMPLOYE_H

