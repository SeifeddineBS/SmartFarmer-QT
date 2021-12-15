#ifndef LIVREUR_H
#define LIVREUR_H

#include <QString>
#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlQuery>



class Livreur
{
public:
    Livreur();
    Livreur(QString,QString,QString,QString,int,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_prenom();
    QString get_tel ();
    int get_exp();
    QString get_mail();
    QString get_voiture();



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * rechercher2(QString);
    QSqlQueryModel * trilivreur();
    QSqlQueryModel * affichervoiture();


private:
    QString nom,prenom,id,mail,tel,voiture;
    int exp;

};


#endif // LIVREUR_H
