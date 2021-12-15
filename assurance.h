#ifndef ASSURANCE_H
#define ASSURANCE_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Assurance
{public:
    Assurance();
   Assurance(QString,QString,QString,QString,QString,int,QString);
    QString get_nom();
    QString get_prenom();
    QString get_type();
    QString get_id();
    QString get_fonction();
    int get_salaire();
     QString get_mail();
    bool ajouter();
    QSqlQueryModel * afficher();
     QSqlQueryModel * affichere();
   // QSqlQueryModel * afficherm();

    QSqlQueryModel * rechercher(QString nom);
    bool supprimer(QString);
     bool modifier();

     QSqlQueryModel * afficher_tri();


private:
    QString nom,prenom,type,id,fonction,mail;
    int salaire ;

};

#endif // ETUDIANT_H
