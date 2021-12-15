#include "livreur.h"
#include <QDebug>
#include "connexion.h"

Livreur::Livreur()
{
    id="";
    nom="";
    prenom="";
    tel="";
    exp=0;
    mail="";
    voiture="";



}

Livreur::Livreur(QString id ,QString nom,QString prenom,QString tel,int exp,QString mail, QString voiture)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->tel=tel;
    this->exp=exp;
    this->mail=mail;
    this->voiture=voiture;

}

QString Livreur::get_id()
{
    return id;
}
QString Livreur::get_nom()
{
    return nom;
}
QString Livreur::get_prenom()
{
    return prenom;
}
QString Livreur::get_tel()
{
    return tel;
}
int Livreur::get_exp()
{
    return exp;

}
QString Livreur::get_mail()
{
    return mail;

}

QString Livreur::get_voiture()
{
    return voiture;

}
    bool Livreur::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO LIVREUR (ID,NOM,PRENOM,TEL,EXP,MAIL,VOITURE)"
              "VALUES (:id, :nom, :prenom, :tel, :exp, :mail, :voiture)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":prenom", prenom);
query.bindValue(":tel", tel);
query.bindValue(":exp", exp);
query.bindValue(":mail", mail);
query.bindValue(":voiture", voiture);



return    query.exec();
}

QSqlQueryModel * Livreur::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from LIVREUR ;");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("TEL"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("EXP"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("MAIL"));
model->setHeaderData(6, Qt::Horizontal,QObject::tr("VOITURE"));



return model;
}

bool Livreur::supprimer(QString id)
{
QSqlQuery query;
query.prepare("DELETE FROM LIVREUR WHERE ID= :id");
query.bindValue(":id",id);
return query.exec();
}

bool Livreur::modifier()
 {     QSqlQuery query;
        query.prepare("UPDATE LIVREUR SET ID=:id,NOM=:nom,PRENOM=:prenom,TEL=:tel,EXP=:exp,MAIL=:mail,VOITURE=:voiture where ID=:id;");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":tel",tel);
        query.bindValue(":exp",exp);
        query.bindValue(":mail",mail);
        query.bindValue(":voiture",voiture);


        return    query.exec();
}

QSqlQueryModel * Livreur::trilivreur()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * FROM LIVREUR ORDER BY EXP DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("TEL"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("EXP"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("VOITURE"));


    return model;
}

QSqlQueryModel * Livreur::rechercher2(QString e )
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * FROM LIVREUR WHERE NOM ='"+e+"' ;");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("TEL"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("EXP"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("MAIL"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("VOITURE"));


    return model ;
}

QSqlQueryModel * Livreur::affichervoiture()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select ID from MATERIEL WHERE TYPE='voiture' ;");


return model;
}
