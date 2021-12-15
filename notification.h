#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QSystemTrayIcon>
#include<QString>
class Notification
{
public:
    Notification();
    void notification_ajoutanimal();
    void notification_ajoutcommande();
    void notification_supprimeranimal();
    void notification_supprimercommande();
    void notification_modifieranimal();
    void notification_modifiercommande();
    void mail_commande();
    void notification_modifierlivraison();
    void notification_supprimerlivraison();
    void notification_ajoutlivraison();





};

#endif // NOTIFICATION_H
