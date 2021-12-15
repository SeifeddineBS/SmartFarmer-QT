#include "commandes.h"
#include<QMessageBox>
#include "connexion.h"

Commande::Commande()
{
    id="";
    idc="";
    dat=QDate();
    prix=0;
}
Commande::Commande(QString id,QDate dat,QString idc,int prix)
{
    this->id=id;
     this->idc=idc;
    this->dat=dat;
    this->prix=prix;

}
int Commande::get_prix(){return prix;}
QDate Commande::get_date(){return dat;}
QString Commande::get_id(){return id;}
QString Commande::get_idc(){return idc;}
bool Commande::ajouter()
{   QSqlQuery query;
    query.prepare("INSERT INTO COMMANDES (ID,DAT,IDC,PRIX)""VALUES(:id,:dat,:idc,:prix)");
    query.bindValue(":id",id);
    query.bindValue(":dat",dat);
    query.bindValue(":idc",idc);
    query.bindValue(":prix",prix);

 return query.exec();
}
bool Commande::supprimer()
{
QSqlQuery query;
query.prepare("Delete from COMMANDES WHERE (ID LIKE '"+id+"')");
return    query.exec();
}
bool Commande::supprimeranimal(QString id)
{
QSqlQuery query;
query.prepare("Delete from ANIMAUX WHERE (ID LIKE '"+id+"')");
return    query.exec();
}
bool Commande::supprimercommandel(QString id)
{
    QSqlQuery query;
    query.prepare("Delete from COMMANDES WHERE (ID LIKE '"+id+"')");
    return    query.exec();
}
bool Commande::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE COMMANDES SET ID=:id, DAT=:dat,IDC=:idc,PRIX=:prix WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":idc",idc);
    query.bindValue(":dat",dat);
    query.bindValue(":prix",prix);


 return query.exec();
}
QSqlQueryModel * Commande::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from COMMANDES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel * Commande::tricommandeas()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM COMMANDES ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel * Commande::tricommandeds()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM COMMANDES ORDER BY PRIX DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel *Commande::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM COMMANDES " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("DATE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}




