#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Fournisseur
{public:
    Fournisseur();
   Fournisseur(QString,QString,QString,QString,QString,int,QString);
    QString get_nom();
    QString get_prenom();
    QString get_type();
    QString get_id();
    QString get_fonction();
    int get_salaire();
     QString get_mail();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficher3();
     QSqlQueryModel * affichere();
   // QSqlQueryModel * afficherm();

    QSqlQueryModel * rechercher(QString nom);
     QSqlQueryModel * trifournisseur();
    bool supprimer(QString);
     bool modifier();

     QSqlQueryModel * afficher_mail();


private:
    QString nom,prenom,type,id,fonction,mail;
    int salaire ;

};

#endif // ETUDIANT_H
