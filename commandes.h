#ifndef COMMANDES_H
#define COMMANDES_H
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>


class Commande
{
public:
    Commande();
    Commande (QString,QDate,QString,int);
    QString get_id();
    QDate get_date();
    QString get_idc();
    int get_prix();
    bool ajouter();
    bool modifier();
    QSqlQueryModel *afficher();
    bool supprimer();
    QSqlQueryModel *tricommandeas();
    QSqlQueryModel *tricommandeds();
   // QSqlQueryModel *recherchecommande(QString id );
    bool supprimeranimal(QString);
    bool supprimercommandel(QString);

    QSqlQueryModel *displayClause(QString cls);
private:
    QDate dat;
    int prix;
    QString id,idc;
};

#endif
