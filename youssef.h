#ifndef YOUSSEF_H
#define YOUSSEF_H

#include <QMainWindow>
#include "nourriture.h"
#include "medicament.h"
#include "fournisseur.h"
#include "evenements.h"
#include "notification.h"



#include <QComboBox>

QT_BEGIN_NAMESPACE
namespace Ui { class Youssef; }
QT_END_NAMESPACE

class Youssef : public QMainWindow
{
    Q_OBJECT

public:
    Youssef(QWidget *parent = nullptr);
    ~Youssef();

private slots:
    void on_pb_ajouter_nour_clicked();
    void on_pb_ajouter_medicament_clicked();


    void on_pb_modifier_medicament_clicked();

    void on_pb_supprimer_nourriture_clicked();

    void on_pb_modifier_nourriture_clicked();

    void on_pb_rechercher_medicament_clicked();

    void on_pb_trier_nourriture_clicked();

    void on_pb_pdf_medicament_clicked();

    void on_pb_pdf_nourriture_clicked();


    void on_pb_supprimer_medicament_clicked();
    void on_pb_confirmer_nourr_clicked();

    void on_pb_confirmer_medicament_clicked();

    void on_pb_ajouter_medicament_2_clicked();

    void on_pb_ajouter_medicament_3_clicked();

    void on_pb_pdf_medicament_2_clicked();

    void on_sendBtn_clicked();
    void mailSent(QString);
    void on_pb_ajouter_evenements_clicked();

    void on_pb_confirmer_evenements_clicked();

    void on_pb_modifier_evenements_clicked();

    void on_pb_supprimer_evenements_clicked();

    void on_pb_rechercher_evenements_clicked();



    void on_pb_trier_evenements_clicked();

private:
    Ui::Youssef *ui;
     Nourriture *tmpnourriture;
     Medicament *tmpmedicament;
     Fournisseur *tmp;
     Evenements *tmpevenements;
     Notification N;


};
#endif
