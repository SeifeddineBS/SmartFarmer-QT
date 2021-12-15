#include "secdialog.h"
#include "ui_secdialog.h"
#include "fournisseur.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "smtp.h"
#include <QString>
#include"QSortFilterProxyModel"
#include <QPrinter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>





SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
      connect(ui->sendbtn, SIGNAL(clicked()),this, SLOT(sendMail()));
      connect(ui->exitbtn, SIGNAL(clicked()),this, SLOT(close()));

    ui->tabetudiant->setModel(tmpfournisseur.afficher());
      ui->comboBox_id->setModel(tmpfournisseur.afficher());
        ui->comboBox_1->setModel(tmpfournisseur.afficher());
        ui->comboBox_20->setModel(tmpfournisseur.affichere());
        ui->comboBox_3->setModel(tmplogin.afficher());
        ui->comboBox_2->setModel(tmplogin.afficher());
        ui->comboBox_id_2->setModel(tmpassurance.afficher());

        ui->comboBox_22->setModel(tmpassurance.affichere());

        ui->comboBox_4->setModel(tmpassurance.afficher());

        ui->comboBox_rcpt->setModel(tmpfournisseur.afficher_mail());


}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::on_pb_ajouter_clicked()
{   QString id= ui->comboBox_20->currentText();

    QString nom= ui->lineEdit_nom->text();
    QString prenom= ui->lineEdit_prenom->text();
    QString type= ui->lineEdit_type->text();
     QString fonction= ui->lineEdit_fonction->text();
      int salaire= ui->lineEdit_salaire->text().toInt();
      QString mail= ui->lineEdit_type_mail->text();


   Fournisseur e(id,nom,prenom,type,fonction,salaire,mail);


  bool test=e.ajouter();
  if(test)
{

         ui->tabetudiant->setModel(tmpfournisseur.afficher());//refresh
         ui->comboBox_id->setModel(tmpfournisseur.afficher());
         ui->comboBox_1->setModel(tmpfournisseur.afficher());
         ui->comboBox_20->setModel(tmpfournisseur.affichere());
         ui->comboBox_rcpt->setModel(tmpfournisseur.afficher_mail());

QMessageBox::information(nullptr, QObject::tr("Ajouter un fournisseur"),
                  QObject::tr("Fournisseur ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else{
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}


void SecDialog::on_pb_supprimer_clicked()
{
    QString id=ui->comboBox_1->currentText();
    bool test=tmpfournisseur.supprimer(id);
    if(test)
    {ui->tabetudiant->setModel(tmpfournisseur.afficher());//refresh
          ui->comboBox_id->setModel(tmpfournisseur.afficher());
          ui->comboBox_1->setModel(tmpfournisseur.afficher());
          ui->comboBox_20->setModel(tmpfournisseur.affichere());
          ui->comboBox_rcpt->setModel(tmpfournisseur.afficher_mail());

        QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Fournisseur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void SecDialog::on_pushButton_Modifier_clicked()
{
    QString id=ui->comboBox_id->currentText();
     QString nom= ui->lineEdit_nom_2->text();
     QString prenom= ui->lineEdit_prenom_2->text();
     QString type= ui->lineEdit_type_2->text();
     QString fonction= ui->lineEdit_fonctiona->text();
      int salaire= ui->lineEdit_salairea->text().toInt();
      QString mail= ui->lineEdit_maila->text();
       QSqlQuery query;
       Fournisseur e(id,nom,prenom,type,fonction,salaire,mail);
      bool test=e.modifier();
      if(test)
    {

          ui->tabetudiant->setModel(tmpfournisseur.afficher());//refresh
          ui->comboBox_1->setModel(tmpfournisseur.afficher());
         // ui->tabetudiantm->setModel(tmpfournisseur.afficherm());
          ui->comboBox_20->setModel(tmpfournisseur.affichere());

          ui->tabetudiant->setModel(tmpfournisseur.afficher());//refresh
          ui->comboBox_id->setModel(tmpfournisseur.afficher());
          ui->comboBox_rcpt->setModel(tmpfournisseur.afficher_mail());

    QMessageBox::information(nullptr, QObject::tr("Modifier fornisseur"),
                      QObject::tr("Fournisseur modifier.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else {
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
 }

       ui->lineEdit_nom_2->clear();
        ui->lineEdit_prenom_2->clear();
         ui->lineEdit_type_2->clear();
         ui->lineEdit_fonctiona->clear();
         ui->lineEdit_salairea->clear();
         ui->lineEdit_maila->clear();


}

void SecDialog::on_pb_recherche_f_clicked()
{
    QString nom=ui->lineEdit_recherche_f->text();
    ui->tabetudiant->setModel(tmpfournisseur.rechercher(nom));
}

void SecDialog::on_pb_tri_clicked()
{
       ui->tabetudiant->setModel(tmpfournisseur.trifournisseur());
}

void SecDialog::on_pb_tri_2_clicked()
{//QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
    QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfFournisseurs.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des FOURNISSEURS");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"ID");
               painter.drawText(1400,3300,"NOM");
               painter.drawText(2600,3300,"Prenom");
               painter.drawText(3800,3300,"Type");
               painter.drawText(5000,3300,"Fonction");
               painter.drawText(6200,3300,"Salaire");
               painter.drawText(7400,3300,"Mail");




               QSqlQuery query;
               query.prepare("select * from FOURNISSEUR");
               query.exec();
               while (query.next())
               {
                   painter.drawText(200,i,query.value(0).toString());
                   painter.drawText(1400,i,query.value(1).toString());
                   painter.drawText(2600,i,query.value(2).toString());
                   painter.drawText(3800,i,query.value(3).toString());
                   painter.drawText(5000,i,query.value(4).toString());
                   painter.drawText(6200,i,query.value(5).toString());
                   painter.drawText(7400,i,query.value(6).toString());


                  i = i + 700;
               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                   if (reponse == QMessageBox::Yes)
                   {
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfFournisseurs.pdf"));

                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }

}

void SecDialog::on_pb_ajouter_2_clicked()
{
    QString username= ui->lineEdit_username_2->text();

    QString nom= ui->lineEdit_nom_6->text();
    QString prenom= ui->lineEdit_prenom_4->text();
     QString password= ui->lineEdit_password_2->text();



  login e(username,nom,prenom,password);
  bool test=e.ajouter();
  if(test)
{

      ui->tabetudiant_2->setModel(tmplogin.afficher());//refresh
      ui->comboBox_3->setModel(tmplogin.afficher());
      ui->comboBox_2->setModel(tmplogin.afficher());
QMessageBox::information(nullptr, QObject::tr("Ajouter Login"),
                  QObject::tr("login ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un login"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void SecDialog::on_pushButton_Modifier_3_clicked()
{
    QString username=ui->comboBox_3->currentText();
     QString nom= ui->lineEdit_nom_5->text();
     QString prenom= ui->lineEdit_prenom_5->text();
     QString password= ui->lineEdit_password_3->text();
      login e(username,nom,prenom,password);
      QSqlQuery query;
      bool test=e.modifier();
      if(test)
    {
          ui->tabetudiant_2->setModel(tmplogin.afficher());//refresh
                    ui->comboBox_2->setModel(tmplogin.afficher());

    QMessageBox::information(nullptr, QObject::tr("Modifier login"),
                      QObject::tr("Login modifier.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else {
          QMessageBox::critical(nullptr, QObject::tr("Ajouter un Login"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
 }

       ui->lineEdit_nom_5->clear();
        ui->lineEdit_prenom_5->clear();
          ui->lineEdit_password_3->clear();
}

void SecDialog::on_pb_supprimer_2_clicked()
{
    QString id=ui->comboBox_2->currentText();
    bool test=tmplogin.supprimer(id);
    if(test)
    {ui->tabetudiant_2->setModel(tmplogin.afficher());//refresh
          ui->comboBox_3->setModel(tmplogin.afficher());
          ui->comboBox_2->setModel(tmplogin.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Fournisseur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void SecDialog::on_pb_recherche_f_2_clicked()
{
    QString nom=ui->lineEdit_recherche_f_2->text();
        ui->tabetudiant_2->setModel(tmplogin.rechercher(nom));

}

void SecDialog::on_pb_tri_f_3_clicked()
{
     ui->tabetudiant_2->setModel(tmplogin.trilogin());
}







void SecDialog::on_pb_ajouter_3_clicked()
{QString id = ui->comboBox_20->currentText();

    QSqlQuery query;
            query.prepare("SELECT * FROM EMPLOYE WHERE ID='"+id+"'");
            if(query.exec())
            {
                while(query.next())
                {   ui->lineEdit_nom->setText(query.value(1).toString());
                    ui->lineEdit_prenom->setText(query.value(2).toString());
                    ui->lineEdit_fonction->setText(query.value(3).toString());
                    ui->lineEdit_salaire->setText(query.value(4).toString());
                    ui->lineEdit_type_mail->setText(query.value(5).toString());


                }

            }
            else
            {
                QObject::tr("ERREUR");
            }

}

void SecDialog::on_pb_ajouter_4_clicked()
{
    QString id = ui->comboBox_id->currentText();

        QSqlQuery query;
                query.prepare("SELECT * FROM FOURNISSEUR WHERE ID='"+id+"'");
                if(query.exec())
                {
                    while(query.next())
                    {   ui->lineEdit_nom_2->setText(query.value(1).toString());
                        ui->lineEdit_prenom_2->setText(query.value(2).toString());
                        ui->lineEdit_type_2->setText(query.value(3).toString());
                        ui->lineEdit_fonctiona->setText(query.value(4).toString());
                        ui->lineEdit_salairea->setText(query.value(5).toString());
                        ui->lineEdit_maila->setText(query.value(6).toString());



                    }

                }
                else
                {
                    QObject::tr("ERREUR");
                }
}

void SecDialog::on_sendbtn_clicked()
{

    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("farmeresprit414@gmail.com",ui->comboBox_rcpt->currentText(), ui->subject->text(),ui->msg->toPlainText());
}
void SecDialog::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_commande();
}


void SecDialog::on_pb_tri_3_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from FOURNISSEUR where salaire < 1000 ");
        float salaire=model->rowCount();
        model->setQuery("select * from FOURNISSEUR where salaire between 1000 and 5000 ");
        float salairee=model->rowCount();
        model->setQuery("select * from FOURNISSEUR where salaire>5000 ");
        float salaireee=model->rowCount();
        float total=salaire+salairee+salaireee;
        QString a=QString("moins de 1000 "+QString::number((salaire*100)/total,'f',2)+"%" );
        QString b=QString("entre 1000 et 5000 "+QString::number((salairee*100)/total,'f',2)+"%" );
        QString c=QString("+5000 "+QString::number((salaireee*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,salaire);
        series->append(b,salairee);
        series->append(c,salaireee);
if (salaire!=0)
{QPieSlice *slice = series->slices().at(0);
 slice->setLabelVisible();
 slice->setPen(QPen());}
if ( salairee!=0)
{
         // Add label, explode and define brush for 2nd slice
         QPieSlice *slice1 = series->slices().at(1);
         //slice1->setExploded();
         slice1->setLabelVisible();
}
if(salaireee!=0)
{
         // Add labels to rest of slices
         QPieSlice *slice2 = series->slices().at(2);
         //slice1->setExploded();
         slice2->setLabelVisible();
}
        // Create the chart widget
        QChart *chart = new QChart();
        // Add data to chart with title and hide legend
        chart->addSeries(series);
        chart->setTitle("Pourcentage Par Salaire:totale de "+ QString::number(total));
        chart->legend()->hide();
        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();
}
void SecDialog::on_pb_ajouter_5_clicked()
{ QString id= ui->comboBox_22->currentText();

    QString nom= ui->lineEdit_nom_3->text();
    QString prenom= ui->lineEdit_prenom_3->text();
    QString type= ui->lineEdit_type_3->text();
     QString fonction= ui->lineEdit_fonction_2->text();
      int salaire= ui->lineEdit_salaire_2->text().toInt();
      QString mail= ui->lineEdit_type_mail_2->text();


   Assurance e(id,nom,prenom,type,fonction,salaire,mail);


  bool test=e.ajouter();
  if(test)
{

         ui->tabetudiant->setModel(tmpassurance.afficher());//refresh
         ui->comboBox_id->setModel(tmpassurance.afficher());
         ui->tabetudiantm_2->setModel(tmpassurance.afficher());
         ui->comboBox_20->setModel(tmpassurance.affichere());
         ui->comboBox_id_2->setModel(tmpassurance.afficher());
         ui->comboBox_22->setModel(tmpassurance.affichere());

         ui->comboBox_4->setModel(tmpassurance.afficher());


QMessageBox::information(nullptr, QObject::tr("Ajouter un fournisseur"),
                  QObject::tr("Fournisseur ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else{
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}}

void SecDialog::on_pb_supprimer_3_clicked()
{ QString id=ui->comboBox_4->currentText();
    bool test=tmpassurance.supprimer(id);
    if(test)
    {ui->tabetudiant->setModel(tmpassurance.afficher());//refresh
          ui->comboBox_id->setModel(tmpassurance.afficher());
          ui->comboBox_4->setModel(tmpassurance.afficher());
          ui->tabetudiantm_2->setModel(tmpassurance.afficher());
          ui->comboBox_22->setModel(tmpassurance.affichere());
          ui->comboBox_id_2->setModel(tmpassurance.afficher());


        QMessageBox::information(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Fournisseur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un fournisseur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}

void SecDialog::on_pb_ajouter_6_clicked()
{QString id = ui->comboBox_22->currentText();

    QSqlQuery query;
            query.prepare("SELECT * FROM EMPLOYE WHERE ID='"+id+"'");
            if(query.exec())
            {
                while(query.next())
                {   ui->lineEdit_nom_3->setText(query.value(1).toString());
                    ui->lineEdit_prenom_3->setText(query.value(2).toString());
                    ui->lineEdit_fonction_2->setText(query.value(3).toString());
                    ui->lineEdit_salaire_2->setText(query.value(4).toString());
                    ui->lineEdit_type_mail_2->setText(query.value(5).toString());




                }

            }
            else
            {
                QObject::tr("ERREUR");
            }


}

void SecDialog::on_pb_ajouter_7_clicked()
{
    QString id = ui->comboBox_id_2->currentText();

        QSqlQuery query;
                query.prepare("SELECT * FROM ASSURENCE WHERE ID='"+id+"'");
                if(query.exec())
                {
                    while(query.next())
                    {   ui->lineEdit_nom_4->setText(query.value(1).toString());
                        ui->lineEdit_prenom_6->setText(query.value(2).toString());
                        ui->lineEdit_type_4->setText(query.value(3).toString());

                        ui->lineEdit_fonctiona_2->setText(query.value(4).toString());

                        ui->lineEdit_salairea_2->setText(query.value(5).toString());
                        ui->lineEdit_maila_2->setText(query.value(6).toString());




                    }

                }
                else
                {
                    QObject::tr("ERREUR");
                }

}

void SecDialog::on_pushButton_Modifier_2_clicked()
{ QString id=ui->comboBox_id_2->currentText();
    QString nom= ui->lineEdit_nom_4->text();
    QString prenom= ui->lineEdit_prenom_6->text();
    QString fonction= ui->lineEdit_fonctiona_2->text();
     int salaire= ui->lineEdit_salairea_2->text().toInt();
     QString type= ui->lineEdit_type_4->text();

     QString mail= ui->lineEdit_maila_2->text();
      QSqlQuery query;
      Assurance e(id,nom,prenom,type,fonction,salaire,mail);
     bool test=e.modifier();
     if(test)
   {
         ui->comboBox_id_2->setModel(tmpassurance.afficher());
         ui->tabetudiantm_2->setModel(tmpassurance.afficher());


   QMessageBox::information(nullptr, QObject::tr("Modifier fornisseur"),
                     QObject::tr("Fournisseur modifier.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);

   }
     else {
         QMessageBox::critical(nullptr, QObject::tr("Ajouter un fournisseur"),
                     QObject::tr("Erreur !.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
}

      ui->lineEdit_nom_2->clear();
       ui->lineEdit_prenom_2->clear();
        ui->lineEdit_type_2->clear();
        ui->lineEdit_fonctiona->clear();
        ui->lineEdit_salairea->clear();
        ui->lineEdit_maila->clear();

}

void SecDialog::on_pb_tri_4_clicked()
{
    ui->tabetudiantm_2->setModel(tmpassurance.afficher_tri());


}

void SecDialog::on_pb_recherche_f_3_clicked()
{
    QString nom=ui->lineEdit_recherche_f_3->text();
        ui->tabetudiantm_2->setModel(tmpassurance.rechercher(nom));
}

void SecDialog::on_pb_ajouter_8_clicked()
{
    QString id = ui->comboBox_3->currentText();

        QSqlQuery query;
                query.prepare("SELECT * FROM LOGIN WHERE USERNAME='"+id+"'");
                if(query.exec())
                {
                    while(query.next())
                    {   ui->lineEdit_nom_5->setText(query.value(1).toString());
                        ui->lineEdit_prenom_5->setText(query.value(2).toString());
                        ui->lineEdit_password_3->setText(query.value(3).toString());





                    }

                }
                else
                {
                    QObject::tr("ERREUR");
                }
}
