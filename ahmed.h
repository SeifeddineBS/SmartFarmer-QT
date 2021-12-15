#ifndef AHMED_H
#define AHMED_H

#include <QMainWindow>
#include "employe.h"
#include "veterinaire.h"
#include "livreur.h"
#include "smtp.h"
#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include "notification.h"



QT_BEGIN_NAMESPACE
namespace Ui { class Ahmed; }
QT_END_NAMESPACE

class Ahmed : public QMainWindow
{
    Q_OBJECT

public:
    Ahmed(QWidget *parent = nullptr);
    ~Ahmed();

private slots:

    void on_pb_ajouter_veterinaire_clicked();

    void on_pb_ajouter_livreur_clicked();

    void on_pb_ajouter_employe_clicked();

    void on_pb_supprimer_employe_clicked();

    void on_pb_modifier_employe_clicked();

    void on_pb_supprimer_veterinaire_clicked();

    void on_pb_supprimer_livreur_clicked();

    void on_pb_modifier_veterinaire_clicked();

    void on_pb_modifier_livreur_clicked();

    void on_pb_pushbutton_tri_clicked();

    void on_pb_pushbutton_tri2_clicked();



    void on_pb_confirmer_clicked();

    void on_pb_confirmer1_clicked();

    void on_pushbutton_rechercher1_clicked();


    void on_pushbutton_rechercher2_clicked();

    void sendMail();

    void mailSent(QString);

    void on_pushbutton_stat_clicked();
    void on_pb_confirmer97_clicked();
    void on_pb_pushbutton_pdf_clicked();
    void on_pushbutton_rechercher_clicked();


    void on_pushbutton_tri1_clicked();

    void on_pb_confirmer99_clicked();

    void on_pb_confirmer98_clicked();


    void on_plus_clicked();
    void on_moins_clicked();
    void on_fois_clicked();
    void on_sur_clicked();

    void on_actionNouveau_triggered();
    void on_actionEnregistrer_triggered();
    void on_actionQuitter_triggered();
    void on_actionCopier_triggered();
    void on_actionColler_triggered();
    void on_actionCoper_triggered();
    void on_actionOuvrir_triggered();
    void on_actionImprimer_triggered();

    void on_pb_pushbutton_pdf_2_clicked();

    void on_pb_pushbutton_pdf_3_clicked();

    void on_pushbutton_stat_2_clicked();

    void on_pushbutton_stat_3_clicked();
    bool testmail(QString);

private:
     Ui::Ahmed *ui;
     Veterinaire *tmpveterinaire;
     Employe *tmpemploye;
     Livreur *tmplivreur;
     QString currentFile = "";
     QSystemTrayIcon *notifier;
     Notification N;


};
#endif // MAINWINDOW_H
