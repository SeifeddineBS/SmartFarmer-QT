#ifndef VETERINAIRE_H
#define VETERINAIRE_H
#include <QString>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDate>

class Veterinaire
{
public:
    Veterinaire();
    Veterinaire(QString,QString,QString,QString,QDate,int,QString);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_specialite ();
    QDate get_diplome();
    int get_exp();
    QString get_mail ();



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * rechercher1(QString);
    QSqlQueryModel * triveterinaire();
    private:
    QString nom,prenom,specialite,id,mail;
    QDate diplome;
    int exp;

};

#endif // NOURRITURE_H
