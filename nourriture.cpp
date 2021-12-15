#include "nourriture.h"
#include <QDebug>
#include "connexion.h"
#include <QComboBox>

Nourriture::Nourriture()
{
    id="";
    nom="";
    type="";
    prix="";
    valid="";
    nomf="";
}

Nourriture::Nourriture(QString id ,QString nom,QString type,QString prix,QString valid,QString nomf)
{
    this->id=id;
    this->nom=nom;
    this->type=type;
    this->prix=prix;
    this->valid=valid;
    this->nomf=nomf;

}
QString Nourriture::get_id()
{
    return id;
}
QString Nourriture::get_nom()
{
    return nom;
}
QString Nourriture::get_type()
{
    return type;
}
QString Nourriture::get_prix()
{
    return prix;
}
QString Nourriture::get_valid()
{
    return valid;
}
QString Nourriture::get_nomf()
{
    return nomf;
}

bool Nourriture::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO NOURRITURE (ID,NOM,TYPE,PRIX,VALID,NOMF)"
              "VALUES (:id, :nom, :type, :prix, :valid,:nomf)");
query.bindValue(":id", id);
query.bindValue(":nom", nom);
query.bindValue(":type", type);
query.bindValue(":prix", prix);
query.bindValue(":valid", valid);
query.bindValue(":nomf", nomf);

return    query.exec();
}

QSqlQueryModel * Nourriture::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from NOURRITURE ;");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("PRIX"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("VALID"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("IDF"));

return model;
}

bool Nourriture::supprimer(QString id)
{
QSqlQuery query;

query.prepare("delete from NOURRITURE where ID= :id");
query.bindValue(":id", id);
return query.exec();
}

bool Nourriture::modifier()
 {     QSqlQuery query;
        query.prepare("UPDATE NOURRITURE SET ID=:id,NOM=:nom,TYPE=:type,PRIX=:prix,VALID=:valid,NOMF=:nomf where ID=:id;");
        query.bindValue(":id",id);
        query.bindValue(":nom",nom);
        query.bindValue(":type",type);
        query.bindValue(":prix",prix);
        query.bindValue(":valid",valid);
        query.bindValue(":nomf", nomf);


        return    query.exec();

}


QSqlQueryModel * Nourriture::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM NOURRITURE ORDER BY PRIX ;");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("VALID"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("NOMF"));


    return model;}
