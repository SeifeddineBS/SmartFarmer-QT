#include "veterinaire.h"
#include <QDebug>
#include "connexion.h"

Veterinaire::Veterinaire()
{
    id="";
    nom="";
    prenom="";
    specialite="";
    diplome= QDate();
    exp=0;
    mail="";

}

Veterinaire::Veterinaire(QString id ,QString nom,QString prenom,QString specialite,QDate diplome,int exp, QString mail)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->specialite=specialite;
    this->diplome=diplome;
    this->exp=exp;
    this->mail=mail;


}
QString Veterinaire::get_id()
{
    return id;
}
QString Veterinaire::get_nom()
{
    return nom;
}
QString Veterinaire::get_prenom()
{
    return prenom;
}
QString Veterinaire::get_specialite()
{
    return specialite;
}
QDate Veterinaire::get_diplome()
{
    return diplome;
}
int Veterinaire::get_exp()
{
    return exp;

}

QString Veterinaire::get_mail()
{
    return mail;
}

    bool Veterinaire::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO VETERINAIRE (ID,NOM,PRENOM,SPECIALITE,DIPLOME,EXP,MAIL)"
              "VALUES (:id, :nom, :prenom, :specialite, :diplome, :exp, :mail)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":specialite", specialite);
query.bindValue(":diplome", diplome);
query.bindValue(":exp", exp);
query.bindValue(":mail", mail);


return    query.exec();
}

QSqlQueryModel * Veterinaire::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from VETERINAIRE ;");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("SPECIALITE"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("DIPLOME"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("EXP"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("MAIL"));


return model;
}

bool Veterinaire::supprimer(QString id)
{
QSqlQuery query;
query.prepare("DELETE FROM VETERINAIRE WHERE ID= :id");
query.bindValue(":id",id);
return query.exec();
}

bool Veterinaire::modifier()
 {     QSqlQuery query;
        query.prepare("UPDATE VETERINAIRE SET ID=:id,NOM=:nom,PRENOM=:prenom,SPECIALITE=:specialite,DIPLOME=:diplome,EXP=:exp,MAIL=:mail where ID=:id;");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":specialite",specialite);
        query.bindValue(":diplome",diplome);
        query.bindValue(":exp",exp);
        query.bindValue(":mail",mail);



        return    query.exec();

}

QSqlQueryModel * Veterinaire::triveterinaire()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM VETERINAIRE ORDER BY EXP DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("SPECIALITE"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DIPLOME"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("EXP"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAIL"));


    return model;
}

QSqlQueryModel * Veterinaire::rechercher1(QString e )
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM VETERINAIRE WHERE NOM ='"+e+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("SPECIALITE"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("DIPLOME"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("EXP"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("MAIL"));

    return model ;
}
