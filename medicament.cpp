#include "medicament.h"
#include <QDebug>
#include "connexion.h"
#include <QComboBox>

Medicament::Medicament()
{
    id="";
    nom="";
    type="";
    prix="";
    maladie="";
    quantite="";
    nomf="";
}

Medicament::Medicament(QString id,QString nom, QString type, QString prix, QString maladie, QString quantite, QString nomf)
{
  this->id=id;
  this->nom=nom;
  this->type=type;
  this->prix=prix;
  this->maladie=maladie;
  this->quantite=quantite;
  this->nomf=nomf;

}
QString Medicament::get_id(){return id;}
QString Medicament::get_nom(){return nom;}
QString Medicament::get_type(){return type;}
QString Medicament::get_prix(){return prix;}
QString Medicament::get_maladie(){return maladie;}
QString Medicament::get_quantite(){return quantite;}
QString Medicament::get_nomf(){return nomf;}

bool Medicament::ajouter()
{
QSqlQuery query;

query.prepare("INSERT INTO MEDICAMENT (ID, NOM, TYPE, PRIX, MALADIE, QUANTITE, NOMF)" "VALUES (:id, :nom, :type, :prix, :maladie, :quantite, :nomf)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":prix", prix);
query.bindValue(":maladie", maladie);
query.bindValue(":quantite", quantite);
query.bindValue(":nomf", nomf);
return    query.exec();
}

QSqlQueryModel * Medicament::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from MEDICAMENT ");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("PRIX"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("MALADIE"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("QUANTITE"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("IDF"));
return model;
}
QSqlQueryModel * Medicament::afficherf()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select ID from FOURNISSEUR");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IDF"));

        return model;}

bool Medicament::supprimer(QString id)
{
QSqlQuery query;

query.prepare("delete from MEDICAMENT where ID= :id");
query.bindValue(":id", id);
return query.exec();
}
bool Medicament::modifier()
 {      QSqlQuery query;

        query.prepare("update MEDICAMENT set ID=:id,NOM=:nom,TYPE=:type,PRIX=:prix,MALADIE=:maladie,QUANTITE=:quantite,NOMF=:nomf where ID=:id");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":type",type);
        query.bindValue(":prix", prix);
        query.bindValue(":maladie", maladie);
        query.bindValue(":quantite", quantite);
        query.bindValue(":nomf",nomf);

        return    query.exec();

}

QSqlQueryModel * Medicament:: rechercher(QString e )
{

    QSqlQueryModel * model= new QSqlQueryModel();

        model->setQuery("SELECT * FROM MEDICAMENT WHERE NOM ='"+e+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("MALADIE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDF"));

    return model ;
}
