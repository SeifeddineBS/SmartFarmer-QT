#ifndef NOURRITURE_H
#define NOURRITURE_H
#include <QString>
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include <QComboBox>

class Nourriture
{
public:
    Nourriture();
    Nourriture(QString,QString,QString,QString,QString,QString);
    QString get_id();
    QString get_nom();
    QString get_type();
    QString get_prix();
    QString get_valid();
    QString get_nomf();
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel * trier();
private:
    QString id,nom,type,prix,valid,nomf;




};

#endif // NOURRITURE_H
