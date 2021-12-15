#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDate>
#include <QDialog>
#include<QSystemTrayIcon>

class Maintenance
{   QString type_pan,agent_maint,note;
    int id_mat;
    QDate date_prise_en_charge;
public:
    Maintenance();
    Maintenance(int,QString,QString,QString ,QDate);

    int get_id_mat();
    QString get_type_pan();
    QString get_agent_maint();
    QString get_note();
    QDate get_date_prise_en_charge();

    bool ajouter();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher1();
    bool modifier();
    bool supprimer(int);
};

#endif // MAINTENANCE_H
