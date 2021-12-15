#include "login.h"
#include <QDebug>
#include "connexion.h"
login::login()
{

nom="";
prenom="";
username="";
password="";
}
login::login(QString username,QString nom,QString prenom,QString password)
{

  this->nom=nom;
  this->prenom=prenom;
    this->username=username;
       this->password=password;
}
QString login::get_nom(){return  nom;}
QString login::get_prenom(){return prenom;}
QString login::get_username(){return  username;}
QString login::get_password(){return  password;}
QString login::get_id(){return  id;}

bool login::ajouter()
{
QSqlQuery query;
//QString res= QString::number(id);
query.prepare("INSERT INTO LOGIN ( USERNAME,NOM,PRENOM,PASSWORD) "
                    "VALUES (  :username,:nom , :prenom, :password)");

query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":username",username);
query.bindValue(":password",password);


return    query.exec();
}

QSqlQueryModel * login::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from LOGIN");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Username"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Password"));
    return model;}


bool login::supprimer(QString id)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from login where USERNAME = :id ");
query.bindValue(":id", id);
return    query.exec();
}
bool login::modifier()
 {  QSqlQuery query;
   // QString res=QString::number(id);
     query.prepare( "UPDATE LOGIN SET USERNAME=:username, NOM=:nom,PRENOM=:prenom,PASSWORD=:password WHERE USERNAME=:username");
     query.bindValue(":username", username);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":password",password);

  return query.exec();

 }

 QSqlQueryModel *login::rechercher(QString nom)
  {   QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("SELECT * FROM LOGIN WHERE NOM ='"+nom+"'");
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Username"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Password"));
          return model;

  }
 QSqlQueryModel *login::trilogin()
 {  QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * FROM LOGIN ORDER BY ID ASC");
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("Username"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("Password"));
        return model;

     return model;
 }

