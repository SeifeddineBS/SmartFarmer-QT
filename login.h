#ifndef LOGIN_H
#define LOGIN_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class login
{public:
    login();
  login (QString,QString,QString,QString);
    QString get_nom();
    QString get_prenom();
    QString get_username();
    QString get_password();
    QString get_id();
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * rechercher(QString nom);
     QSqlQueryModel * trilogin();
    bool supprimer(QString);
     bool modifier();


private:
    QString id,nom,prenom,username,password;


};

#endif //
