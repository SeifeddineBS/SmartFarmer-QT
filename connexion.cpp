#include "connexion.h"
#include <qsqldatabase.h>
Connexion::Connexion()
{

}
bool Connexion::connecter()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("ProjetQT");
db.setUserName("Seif");//inserer nom de l'utilisateur
db.setPassword("0000");//inserer mot de passe de cet utilisateur
if(db.open())
return true;
return false;

}
