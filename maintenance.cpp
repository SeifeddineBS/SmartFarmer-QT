#include "maintenance.h"
#include<QDate>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include "connexion.h"
#include"materiel.h"
Maintenance::Maintenance()
{
    id_mat=0;
    type_pan="";
    agent_maint="";
    date_prise_en_charge=QDate();
    note="";
}
Maintenance::Maintenance(int id_mat,QString type_pan,QString note,QString agent_maint,QDate date_prise_en_charge)
{
    this->id_mat=id_mat;
    this->type_pan=type_pan;
    this->note=note;
    this->agent_maint=agent_maint;
    this->date_prise_en_charge=date_prise_en_charge;

}

int Maintenance::get_id_mat(){return id_mat;}
QString Maintenance::get_type_pan(){return type_pan;}
QString Maintenance::get_note(){return note;}
QString Maintenance::get_agent_maint(){return agent_maint;}
QDate Maintenance::get_date_prise_en_charge(){return date_prise_en_charge;}


bool Maintenance::ajouter()
{   QSqlQuery query;
    QString res=QString::number(id_mat);
    query.prepare("INSERT INTO MAINTENANCE(ID_MAT,TYPEPAN,NOTE,AGENTMAINT,DPRISEENCHARGE)""VALUES(:id_mat,:type_pan,:note,:agent_maint,:date_prise_en_charge)");
    query.bindValue(":id_mat",res);
    query.bindValue(":type_pan",type_pan);
    query.bindValue(":note",note);
    query.bindValue(":agent_maint",agent_maint);
    query.bindValue(":date_prise_en_charge",date_prise_en_charge);

 return query.exec();
}

QSqlQueryModel * Maintenance::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM MAINTENANCE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("type de panne "));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("note"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("agent de maint"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date.P.E.C"));

    return model;
}
QSqlQueryModel * Maintenance::afficher1()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT PRENOM FROM EMPLOYE where FONCTION='maintenance'");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifiant"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("fonction"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire"));

    return model;
}

bool Maintenance::supprimer(int id_mat)
{
QSqlQuery query;
QString res= QString::number(id_mat);
query.prepare("DELETE FROM MAINTENANCE WHERE ID_MAT = :id_mat");
query.bindValue(":id_mat", res);
return    query.exec();
}

bool Maintenance::modifier()
{   QSqlQuery query;
    QString res=QString::number(id_mat);
    query.prepare( "UPDATE MAINTENANCE SET ID_MAT=:id_mat,TYPEPAN=:type_pan,AGENTMAINT=:agent_maint,DPRISEENCHARGE=:date_prise_en_charge,NOTE=:note WHERE ID_MAT=:id_mat");
    query.bindValue(":id_mat",res);
    query.bindValue(":type_pan",type_pan);
    query.bindValue(":agent_maint",agent_maint);
    query.bindValue(":date_prise_en_charge",date_prise_en_charge);
    query.bindValue(":note",note);
 return query.exec();
}


