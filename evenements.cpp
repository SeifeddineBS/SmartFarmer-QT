#include "evenements.h"
#include <QDebug>
#include <QDate>
#include "connexion.h"

Evenements::Evenements()
{
    id="";
    nom="";
    type="";
    lieu="";
    datee=QDate();

}
Evenements::Evenements(QString id,QString nom, QString type, QString lieu, QDate datee)
{
  this->id=id;
  this->nom=nom;
  this->type=type;
  this->lieu=lieu;
  this->datee=datee;



}
QString Evenements::get_id(){return id;}
QString Evenements::get_nom(){return nom;}
QString Evenements::get_type(){return type;}
QString Evenements::get_lieu(){return lieu;}
QDate Evenements::get_datee(){return datee;}

bool Evenements::ajouter()
{
QSqlQuery query; //La classe QSqlQuery fournit un moyen d'exécuter et de manipuler des instructions SQL et récuperer les requettes

query.prepare("INSERT INTO EVENEMENTS (ID, NOM, TYPE, LIEU, DATEE)" "VALUES (:id, :nom, :type, :lieu, :datee)");
query.bindValue(":id", id); //bindValue torbot binet el values eli fl table ou el values eli andek fl program
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":lieu", lieu);
query.bindValue(":datee", datee);
return    query.exec();
}

QSqlQueryModel * Evenements::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel(); //QSqlQueryModel est une interface de haut niveau pour exécuter des instructions SQL et parcourir l'ensemble de résultats et fournir des données pour afficher des classes
model->setQuery("select * from EVENEMENTS ");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID")); //setHeaderData:Pour modifier les textes d'en-tête
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("LIEU"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("DATEE"));

return model;}

bool Evenements::supprimer(QString id)
{
QSqlQuery query;

query.prepare("delete from EVENEMENTS where ID= :id");
query.bindValue(":id", id);
return query.exec();
}

bool Evenements::modifier()
 {      QSqlQuery query;

        query.prepare("update EVENEMENTS set ID=:id,NOM=:nom,TYPE=:type,LIEU=:lieu,DATEE=:datee where ID=:id");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":type",type);
        query.bindValue(":lieu", lieu);
        query.bindValue(":datee", datee);

        return    query.exec();

}

QSqlQueryModel * Evenements:: rechercher(QString ev )
{

    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM EVENEMENTS WHERE NOM ='"+ev+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEE"));

    return model ;
}

QSqlQueryModel * Evenements::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM EVENEMENTS ORDER BY ID ;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("LIEU"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEE"));

    return model;}
