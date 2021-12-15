#include "assurance.h"
#include <QDebug>
#include "connexion.h"
Assurance::Assurance()
{
id="";
nom="";
prenom="";
type="";
fonction="";
salaire=0;
type="";
mail="";
}
Assurance::Assurance(QString id,QString nom,QString prenom,QString type,QString fonction,int salaire,QString mail)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->type=type;
    this->fonction=fonction;
    this->salaire=salaire;
    this->mail=mail;
}

QString Assurance::get_nom(){return  nom;}
QString Assurance::get_prenom(){return prenom;}
QString Assurance::get_type(){return  type;}
QString Assurance::get_id(){return  id;}
QString Assurance::get_fonction(){return  fonction;}
int Assurance::get_salaire(){return  salaire;}
QString Assurance::get_mail(){return  mail;}
bool Assurance::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO ASSURENCE (ID,NOM,PRENOM,FONCTION,SALAIRE,MAIL,TYPE)"
              "VALUES (:id,:nom,:prenom,:fonction,:salaire,:mail,:type)");
query.bindValue(":id",id);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);

query.bindValue(":fonction",fonction);
query.bindValue(":salaire",salaire);
query.bindValue(":mail",mail);
query.bindValue(":type",type);


return    query.exec();
}

QSqlQueryModel * Assurance::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from ASSURENCE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fonction"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mail"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type"));

    return model;}




bool Assurance::supprimer(QString id)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from ASSURENCE where ID = :id ");
query.bindValue(":id", id);
return    query.exec();
}
 bool Assurance::modifier()
 {  QSqlQuery query;
     //QString res=QString::Q(id);
     query.prepare( "UPDATE ASSURENCE SET ID=:id, NOM=:nom,PRENOM=:prenom,FONCTION=:fonction,SALAIRE=:salaire,MAIL=:mail,TYPE=:type WHERE ID=:id");
    query.bindValue(":id", id);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);

     query.bindValue(":fonction", fonction);
     query.bindValue(":salaire", salaire);
     query.bindValue(":mail", mail);
      query.bindValue(":type", type);

  return query.exec();

 }

 QSqlQueryModel *Assurance::rechercher(QString nom)
  {   QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("SELECT * FROM ASSURENCE WHERE ID ='"+nom+"'");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fonction"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mail"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type"));
          return model;

  }
 QSqlQueryModel * Assurance::afficher_tri()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * FROM ASSURENCE ORDER BY ID ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Fonction"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Salaire"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mail"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Type"));


     return model;
 }
 QSqlQueryModel * Assurance::affichere()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from EMPLOYE ");

     return model;}





