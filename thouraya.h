#ifndef THOU_H
#define THOU_H

//#include<QSystemTrayIcon>
//#include<QSqlQueryModel>
#include <QMainWindow>
#include "maintenance.h"
#include "materiel.h"
#include "youssef.h"
#include "nizar.h"
#include "animaux.h"
#include "secdialog.h"
#include "ahmed.h"

//les include de la partie notepad
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Thou; }
QT_END_NAMESPACE

class Thou : public QMainWindow
{
    Q_OBJECT

public:
    Thou(QWidget *parent = nullptr);
    ~Thou();
   //QSqlQueryModel *afficher();
    //bool supprimer(int);


private slots:

void on_pushButton_clicked();
    void on_youssef_clicked();
    void on_seif_clicked();
    void on_ahmed_clicked();
    void on_adem_clicked();
    void on_nizar_clicked();
    void on_retour_clicked();
    void on_retour2_clicked();
    void on_pushButton_supprimer_maint_clicked();

    void on_pushButton_ajoutermateriel_clicked();

    void on_pushButton_modifier_materiel_clicked();

    void on_chercher_clicked();

    void on_pushButton_supprimer_materiel_clicked();

    void on_pushButton_ajouter_maintenance_clicked();

    void on_modifie_maintenance_clicked();

    void on_pushButton_notepad_clicked();

    void on_actionNEW_triggered();

    void on_actionOPEN_triggered();

    void on_actionSAVE_AS_triggered();

    void on_actionPRINT_triggered();

    void on_actionEXIT_triggered();

    void on_actionCOPY_triggered();

    void on_actionPASTE_triggered();

    void on_actionCUT_triggered();

    void on_actionUNDO_triggered();

    void on_actionREDO_triggered();

    void on_pushButton_imprimer_clicked();

    void on_pushButton_imprimer_2_clicked();

    void on_pushButton_2_clicked();

  void on_comboBoxid_currentIndexChanged(int index);

   void on_comboBox1_currentIndexChanged(int index);



   //void on_pushButton_confirm_clicked();


   void on_pushButton_3_clicked();




   void on_pushButton_8_clicked();

   void on_pushButton_10_clicked();

   void on_pushButton_11_clicked();

   void on_pushButton_12_clicked();

  // void on_comboboxmaintajout_currentIndexChanged(int index);

   void on_pushmodifmaint_clicked();

   void on_combomodifmaint_currentIndexChanged(int index);

   void on_pushButton_13_clicked();



private:
    Ui::Thou *ui;
    Youssef *youss;
    Ahmed *ahm;
    Nizar *niz;


    Animal *anim;
    SecDialog *sec;
    //Ui::Maintenance *ui;
    Maintenance *tmpmaint;
    Materiel *tmpmateriel;
    QSystemTrayIcon *notifier;
    // A Qt character string that will hold text entered by the user
        QString currentFile = "";

};
#endif // THOU_H

