#include "fournisseur.h"
#include <QDebug>
#include "connexion.h"
Fournisseur::Fournisseur()
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
Fournisseur::Fournisseur(QString id,QString nom,QString prenom,QString type,QString fonction,int salaire,QString mail)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->type=type;
    this->fonction=fonction;
    this->salaire=salaire;
    this->mail=mail;
}

QString Fournisseur::get_nom(){return  nom;}
QString Fournisseur::get_prenom(){return prenom;}
QString Fournisseur::get_type(){return  type;}
QString Fournisseur::get_id(){return  id;}
QString Fournisseur::get_fonction(){return  fonction;}
int Fournisseur::get_salaire(){return  salaire;}
QString Fournisseur::get_mail(){return  mail;}

bool Fournisseur::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO FOURNISSEUR (ID,NOM,PRENOM,TYPE,FONCTION,SALAIRE,MAIL)"
              "VALUES (:id,:nom,:prenom,:type,:fonction,:salaire,:mail)");
query.bindValue(":id",id);
query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":type",type);
query.bindValue(":fonction",fonction);
query.bindValue(":salaire",salaire);
query.bindValue(":mail",mail);


return    query.exec();
}

QSqlQueryModel * Fournisseur::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from FOURNISSEUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mail"));
    return model;}




bool Fournisseur::supprimer(QString id)
{
QSqlQuery query;
//QString res= QString::number(idd);
query.prepare("Delete from FOURNISSEUR where ID = :id ");
query.bindValue(":id", id);
return    query.exec();
}
 bool Fournisseur::modifier()
 {  QSqlQuery query;
     //QString res=QString::Q(id);
     query.prepare( "UPDATE FOURNISSEUR SET ID=:id, NOM=:nom,PRENOM=:prenom,TYPE=:type,FONCTION=:fonction,SALAIRE=:salaire,MAIL=:mail WHERE ID=:id");
    query.bindValue(":id", id);
     query.bindValue(":nom", nom);
     query.bindValue(":prenom", prenom);
     query.bindValue(":type", type);
     query.bindValue(":fonction", fonction);
     query.bindValue(":salaire", salaire);
     query.bindValue(":mail", mail);

  return query.exec();

 }

 QSqlQueryModel *Fournisseur::rechercher(QString nom)
  {   QSqlQueryModel * model= new QSqlQueryModel();
       model->setQuery("SELECT * FROM FOURNISSEUR WHERE NOM ='"+nom+"'");
       model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
       model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
       model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));
          return model;

  }
 QSqlQueryModel * Fournisseur::trifournisseur()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * FROM FOURNISSEUR ORDER BY ID ASC");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Mail"));

     return model;
 }
 QSqlQueryModel * Fournisseur::affichere()
 {QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select * from EMPLOYE where FONCTION='fournisseur'");
 model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
 model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom "));
 model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prénom"));
 model->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"));
 model->setHeaderData(4, Qt::Horizontal, QObject::tr("Fonction"));
 model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salaire"));
 model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mail"));
     return model;}
 QSqlQueryModel * Fournisseur::afficher_mail()
 {
    QSqlQueryModel * model= new QSqlQueryModel();
 model->setQuery("select MAIL from FOURNISSEUR ");
     return model;}


