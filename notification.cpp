#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>
Notification::Notification()
{

}

void Notification::notification_ajoutanimal()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion d'Animaux ","Nouveau animal ajouté ",QSystemTrayIcon::Information,15000);
}
void Notification::notification_ajoutcommande()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Nouvelle Commande ajoutée ",QSystemTrayIcon::Information,15000);
}
void Notification::notification_supprimeranimal(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Animaux ","Animal Supprimé",QSystemTrayIcon::Information,15000);
}
void Notification::notification_supprimercommande(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Une Commande est supprimée",QSystemTrayIcon::Information,15000);

}
void Notification::notification_modifiercommande(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Commandes ","Une Commande est modifiée",QSystemTrayIcon::Information,15000);

}
void Notification::notification_modifieranimal(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Animaux ","Un Animal est modifié",QSystemTrayIcon::Information,15000);

}
void Notification::mail_commande(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("","Votre Mail est envoyé :)",QSystemTrayIcon::Information,15000);

}

void Notification::notification_modifierlivraison(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Livraisons ","Une Livraison est modifié",QSystemTrayIcon::Information,15000);

}
void Notification::notification_supprimerlivraison(){
    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Livraisons ","Livraisone Supprimée",QSystemTrayIcon::Information,15000);
}
void Notification::notification_ajoutlivraison()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

   // notifyIcon->setIcon(QIcon(":/new/prefix1/MyResources/computer-icons-avatar-user-login-avatar.jpg"));
    notifyIcon->show();
    notifyIcon->showMessage("Gestion des Livraisons ","Nouvelle livraison ajoutée ",QSystemTrayIcon::Information,15000);
}


