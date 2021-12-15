#ifndef livraisonS_H
#define livraisonS_H
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>


class Livraison
{
public:
    Livraison();
    Livraison (QString,QString,QString,QDate,int,QString);
    QString get_id();
    QDate get_dat();
    QString get_idl();
    QString get_idc();
    QString get_lieu();
    int get_prix();
    bool ajouterl();
    bool modifierl();
    QSqlQueryModel *afficherl();
    QSqlQueryModel *afficherlivreur();
    bool supprimerl();
    QSqlQueryModel *trilivraisonas();
    QSqlQueryModel *trilivraisonds();
   // QSqlQueryModel *recherchelivraison(QString id );
    bool supprimercommande(QString);
    QSqlQueryModel *displayClause(QString cls);
private:
    QDate dat;
    int prix;
    QString id,idc,idl,lieu;
};

#endif
