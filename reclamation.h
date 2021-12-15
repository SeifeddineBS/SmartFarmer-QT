#ifndef reclamation_H
#define reclamation_H
#include<QString>
#include<QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

class reclamation
{
     QDate date_creation;
     QString code,cin;
public:
    reclamation();
    reclamation(QString,QString,QDate);
    QString getcode(){return code;}
    void setcode(QString code){this->code=code;}
    void setdate_creation(QDate date_creation){this->date_creation=date_creation;}
    bool ajouter_reclamation();
    QSqlQueryModel * afficher_reclamation();
    QSqlQueryModel * afficherC();
    bool supprimer_reclamation(QString);
 bool rech(QString);
        bool modifier(QString,QDate);
        QSqlQueryModel * afficher_reclamation_ch(QString);
        QSqlQueryModel * trierreclamation_code();
        QSqlQueryModel * Rechercher(QString);

       // bool  rech_reclamation(int code);


    ~reclamation(){}

};

#endif // Creclamation_H
