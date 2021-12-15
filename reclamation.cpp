#include "reclamation.h"
#include<QSqlQuery>
#include<QString>
#include<QDate>
#include<QVariant>


reclamation::reclamation()
{
    code="";

}


reclamation::reclamation(QString code,QString cin,QDate date_creation)
{
    this->code=code;
    this->cin=cin;
    this->date_creation=date_creation;
}

bool reclamation::ajouter_reclamation()
{
    QSqlQuery query;

          query.prepare("INSERT INTO reclamation (code,cin,date_creation) "
                        "VALUES (:code,:cin, :date_creation)");
          query.bindValue(":code", code);
          query.bindValue(":cin", cin);
          query.bindValue(":date_creation", date_creation);


          return  query.exec();
}

QSqlQueryModel * reclamation::afficher_reclamation()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from reclamation");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Creation "));
    return model;
}
QSqlQueryModel * reclamation::afficherC()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select c.CIN ,concat(c.NOM,concat(' ',c.PRENOM)),count(*) from RECLAMATION r inner join CLIENT c on c.CIN=r.CIN group by(c.CIN)");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    return model;
}
bool reclamation::supprimer_reclamation(QString code)
{
QSqlQuery query;
query.prepare("Delete from reclamation where code = :code ");
query.bindValue(":code", code);
return    query.exec();
}

bool reclamation::rech(QString code){
    QSqlQuery query;
    query.prepare("select * from reclamation where code = :code");
    query.bindValue(":code", code);
    return query.exec();
}

bool reclamation::modifier(QString code,QDate date_creation){
    QSqlQuery query;
    query.prepare("update reclamation set date_creation=:date_creation where code = :code");
    query.bindValue(":code", code);
    query.bindValue(":date_creation", date_creation);
    return query.exec();
}


QSqlQueryModel * reclamation::trierreclamation_code()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from reclamation ORDER BY Code");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Creation"));
        return model;
}



QSqlQueryModel * reclamation::afficher_reclamation_ch(QString code)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QSqlQuery query;
    model->setQuery("select Code,Cin,Date_Creation from reclamation WHERE regexp_like(Code,:code)");
    query.bindValue(":code", code);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date_Creation"));
        return model;
}

/*bool reclamation::rech_reclamation(int code){
    QSqlQuery query;
    QString res=QString::number(code);
    query.prepare("select * from reclamation where regexp_like(Code,:code)");
    query.bindValue(":code", res);

    return query.exec();
}*/
QSqlQueryModel * reclamation::Rechercher(QString code)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from reclamation where (code LIKE '"+code+"%' ) ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code"));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));

            return  model;


}

