#include "employe.h"
#include <QDebug>
#include "connexion.h"

Employe::Employe()
{
    id="";
    nom="";
    prenom="";
    fonction="";
    salaire=0;
    mail="";
}

Employe::Employe(QString id,QString nom, QString prenom, QString fonction, int salaire, QString mail)
{
  this->id=id;
  this->nom=nom;
  this->prenom=prenom;
  this->fonction=fonction;
  this->salaire=salaire;
  this->mail=mail;
}

QString Employe::get_id()
{return id;}
QString Employe::get_nom(){return nom;}
QString Employe::get_prenom(){return prenom;}
QString Employe::get_fonction(){return fonction;}
int Employe::get_salaire(){return salaire;}
QString Employe::get_mail(){return mail;}


bool Employe::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO EMPLOYE (ID, NOM, PRENOM, FONCTION, SALAIRE, MAIL)" "VALUES (:id, :nom, :prenom, :fonction, :salaire, :mail)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":fonction", fonction);
query.bindValue(":salaire", salaire);
query.bindValue(":mail", mail);

return    query.exec();
}

QSqlQueryModel * Employe::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from EMPLOYE ");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("FONCTION"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));

return model;
}
QSqlQueryModel * Employe::afficher_livreur()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from EMPLOYE where FONCTION='livreur'");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("FONCTION"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));

return model;
}
QSqlQueryModel * Employe::afficher_vet()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from EMPLOYE where FONCTION='veterinaire'");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("FONCTION"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("SALAIRE"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));

return model;
}

bool Employe::supprimer(QString id)
{
QSqlQuery query;
query.prepare("delete from EMPLOYE where ID= :id");
query.bindValue(":id", id);
return query.exec();
}
bool Employe::modifier()
 {      QSqlQuery query;
        query.prepare("update EMPLOYE set ID=:id,NOM=:nom,PRENOM=:prenom,FONCTION=:fonction,SALAIRE=:salaire, MAIL=:mail where ID=:id");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":fonction", fonction);
        query.bindValue(":salaire", salaire);
        query.bindValue(":mail", mail);

        return    query.exec();
}

QSqlQueryModel * Employe::rechercher(QString e )
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM EMPLOYE WHERE NOM ='"+e+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTION"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));

    return model ;
}

QSqlQueryModel * Employe::triemploye()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM EMPLOYE ORDER BY SALAIRE DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("FONCTION"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("SALAIRE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));


    return model;
}

QSqlQueryModel * Employe::afficher1()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select MAIL from EMPLOYE");
model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));

return model;
}

