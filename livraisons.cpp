#include "livraisons.h"
#include<QMessageBox>
#include "connexion.h"

Livraison::Livraison()
{
    id="";
    idc="";
    idl="";
    lieu="";
    dat=QDate();
    prix=0;
}
Livraison::Livraison(QString id,QString idc,QString idl,QDate dat,int prix,QString lieu)
{
    this->id=id;
     this->idc=idc;
    this->idl=idl;
    this->dat=dat;
    this->prix=prix;
    this->lieu=lieu;


}
int Livraison::get_prix(){return prix;}
QDate Livraison::get_dat(){return dat;}
QString Livraison::get_id(){return id;}
QString Livraison::get_idc(){return idc;}
QString Livraison::get_idl(){return idl;}
QString Livraison::get_lieu(){return lieu;}


bool Livraison::ajouterl()
{   QSqlQuery query;
    query.prepare("INSERT INTO LIVRAISONS (ID,IDC,IDL,DAT,PRIX,LIEU)""VALUES(:id,:idc,:idl,:dat,:prix,:lieu)");
    query.bindValue(":id",id);
    query.bindValue(":idc",idc);
    query.bindValue(":idl",idl);
    query.bindValue(":dat",dat);
    query.bindValue(":prix",prix);
    query.bindValue(":lieu",lieu);


 return query.exec();
}
bool Livraison::supprimerl()
{
QSqlQuery query;
query.prepare("Delete from LIVRAISONS WHERE (ID LIKE '"+id+"')");
return    query.exec();
}
bool Livraison::supprimercommande(QString id)
{
QSqlQuery query;
query.prepare("Delete from COMMANDES WHERE (ID LIKE '"+id+"')");
return    query.exec();
}
bool Livraison::modifierl()
{   QSqlQuery query;
    query.prepare( "UPDATE LIVRAISONS SET ID=:id,IDC=:idc,IDL=:idl,DAT=:dat,PRIX=:prix,LIEU=:lieu WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":idc",idc);
    query.bindValue(":idc",idl);
    query.bindValue(":dat",dat);
    query.bindValue(":prix",prix);
    query.bindValue(":lieu",lieu);



 return query.exec();
}
QSqlQueryModel * Livraison::afficherl()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from LIVRAISONS");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDL"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LIEU"));


    return model;
}
QSqlQueryModel * Livraison::afficherlivreur()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from LIVREUR");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));


    return model;
}
QSqlQueryModel * Livraison::trilivraisonas()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM LIVRAISONS ORDER BY PRIX ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDL"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LIEU"));


    return model;
}
QSqlQueryModel * Livraison::trilivraisonds()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM LIVRAISONS ORDER BY PRIX DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDL"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DAT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LIEU"));


    return model;
}
QSqlQueryModel *Livraison::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM LIVRAISONS " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("IDC"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("IDL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("LIEU"));

    return model;
}




