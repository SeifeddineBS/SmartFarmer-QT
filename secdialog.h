#ifndef SECDIALOG_H
#define SECDIALOG_H
#include "fournisseur.h"
#include <QDialog>
#include <QMainWindow>
#include "login.h"
#include "smtp.h"
#include <QString>
#include <QtCharts>
#include <QLineSeries>
#include <QChartView>
#include "assurance.h"
#include "notification.h"


namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = 0);
    ~SecDialog();

private slots:
    void on_pb_ajouter_clicked();

        void mailSent(QString);

    void on_pb_supprimer_clicked();

    void on_pushButton_Modifier_clicked();

    void on_pb_recherche_f_clicked();

    void on_pb_tri_clicked();

    void on_pb_tri_2_clicked();

    void on_pb_ajouter_2_clicked();

    void on_pushButton_Modifier_3_clicked();



    void on_pb_supprimer_2_clicked();

    void on_pb_recherche_f_2_clicked();

    void on_pb_tri_f_3_clicked();


    void on_pb_ajouter_3_clicked();

    void on_pb_ajouter_4_clicked();

    void on_sendbtn_clicked();


    void on_pb_tri_3_clicked();
    void on_pb_ajouter_5_clicked();

        void on_pb_supprimer_3_clicked();

        void on_pb_ajouter_6_clicked();

        void on_pb_ajouter_7_clicked();

        void on_pushButton_Modifier_2_clicked();

        void on_pb_tri_4_clicked();

        void on_pb_recherche_f_3_clicked();

        void on_pb_ajouter_8_clicked();

private:
    Ui::SecDialog *ui;
     Fournisseur tmpfournisseur;
     login tmplogin ;
     Assurance tmpassurance;
     Notification N;




};

#endif // SECDIALOG_H
