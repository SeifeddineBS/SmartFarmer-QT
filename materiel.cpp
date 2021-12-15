#include "materiel.h"

Materiel::Materiel()
{
    id=0;
    type="";
    etat="";
    dateachat= QDate();
    maint="";
}
Materiel::Materiel(int id,QString type,QString etat,QDate dateachat,QString maint)
{
    this->id=id;
     this->type=type;
     this->etat=etat;
    this->dateachat=dateachat;
    this->maint=maint;
}
QString Materiel::get_type(){return type;}
QString Materiel::get_etat(){return etat;}
QDate Materiel::get_dateachat(){return dateachat;}
QString Materiel::get_maint(){return maint;}
int Materiel::get_id(){return id;}
//QString Materiel::get_id(){return id;}
bool Materiel::ajouter()
{   QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("INSERT INTO MATERIEL (ID,TYPE,ETAT,DATEACHAT,MAINT)""VALUES(:id,:type,:etat,:dateachat,:maint)");
    query.bindValue(":id",res);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":dateachat",dateachat);
    query.bindValue(":maint",maint);
 return query.exec();
}
bool Materiel::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from MATERIEL where ID = :id ");
query.bindValue(":id", res);
return    query.exec();
}

/*bool Materiel::modifier()
{   QSqlQuery query;
    QString res=QString::number(id);
    query.prepare( "UPDATE MATERIEL SET ID=:mm.id, TYPE=:mm.type,ETAT=:mm.etat,DATEACHAT=:mm.dateachat,MAINT=:mm.maint WHERE ID=:mm.id");
    query.bindValue(":mm.id",res);
    query.bindValue(":mm.type",type);
    query.bindValue(":mm.etat",etat);
    query.bindValue(":mm.dateachat",dateachat);
    query.bindValue(":mm.maint",maint);
 return query.exec();

}
*/
QSqlQueryModel * Materiel::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from materiel");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE D'ACHAT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAINTENANCE"));
    return model;
}
QSqlQueryModel * Materiel::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select ID from materiel where maint='oui' ");
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(0, Qt::Horizontal, QObject::tr("TYPE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE D'ACHAT"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAINTENANCE"));
    return model;
}

QSqlQueryModel *Materiel::cherchermateriel(int id)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("select * from materiel where id= ? ");
    query.addBindValue(id);
    query.exec();


    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("TYPE "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ETAT"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE D'ACHAT"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("MAINTENANCE"));



  return model;
}


