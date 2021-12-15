#ifndef MEDICAMENT_H
#define MEDICAMENT_H
#include <QString>
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QComboBox>

class Medicament
{
public:
    Medicament();
    Medicament(QString,QString,QString,QString,QString,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_type();
    QString get_prix();
    QString get_maladie();
    QString get_quantite();
    QString get_nomf();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherf();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * rechercher (QString e );
private:
    QString id,nom,type,prix,maladie,quantite,nomf;

};

#endif // MEDICAMENT_H

