#include "youssef.h"
#include "ui_youssef.h"
#include <QMessageBox>
#include "nourriture.h"
#include "medicament.h"
#include "connexion.h"
#include <QPainter>
#include <QPdfWriter>
#include <QComboBox>
#include <QPrinter>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts/QChartView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include "smtp.h"
#include"QSortFilterProxyModel"
QT_CHARTS_USE_NAMESPACE


Youssef::Youssef(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Youssef)
{
    ui->setupUi(this);

    ui->tabnourriture->setModel(tmpnourriture->afficher());
    ui->tabmedicament->setModel(tmpmedicament->afficher());
    ui->comboBox_3->setModel(tmpnourriture->afficher());
    ui->comboBox_5->setModel(tmpmedicament->afficherf());
    ui->comboBox_6->setModel(tmpmedicament->afficherf());
    ui->comboBox_fournisseur->setModel(tmpmedicament->afficherf());
    ui->comboBox_fournisseur1->setModel(tmpmedicament->afficherf());

    ui->comboBox_7->setModel(tmp->afficher_mail());
    ui->comboBox_2->setModel(tmpnourriture->afficher());
    ui->comboBox_4->setModel(tmpmedicament->afficher());
    ui->comboBox->setModel(tmpmedicament->afficher());

    ui->comboBox_8_ev->setModel(tmpevenements->afficher());
    ui->comboBox_10_ev->setModel(tmpevenements->afficher());



}

Youssef::~Youssef()
{
    delete ui;
}


void Youssef::on_pb_ajouter_nour_clicked()
{
        QString id = ui->lineEdit_id->text();
        QString nom = ui->lineEdit_nom->text();
        QString type = ui->lineEdit_type->text();
        QString prix = ui->lineEdit_prix->text();
        QString valid = ui->lineEdit_valid->text();
        QString nomf= ui->comboBox_fournisseur->currentText();

        Nourriture n(id,nom,type,prix,valid,nomf);

      bool test=n.ajouter();
      if(test)
      { ui->tabnourriture->setModel(tmpnourriture->afficher());
          ui->comboBox_3->setModel(tmpnourriture->afficher());
          ui->comboBox_2->setModel(tmpnourriture->afficher());


          QMessageBox::information(nullptr, QObject::tr("Ajouter nourriture"),
                            QObject::tr("Nourriture ajouté.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

    }
      else
          QMessageBox::critical(nullptr, QObject::tr("Ajouter nourriture"),
                      QObject::tr("Erreur !.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void Youssef::on_pb_ajouter_medicament_clicked()
{
    QString id = ui->lineEdit_id_2->text();
    QString nom = ui->lineEdit_2_nom->text();
    QString type = ui->lineEdit_3_type->text();
    QString prix = ui->lineEdit_4_prix->text();
    QString maladie = ui->lineEdit_5_maladie->text();
    QString quantite = ui->lineEdit_6_quantite->text();
    QString nomf = ui->comboBox_5->currentText();

  Medicament m(id,nom,type,prix,maladie,quantite,nomf);
  bool test=m.ajouter();
  if(test)
  {   ui->tabmedicament ->setModel(tmpmedicament->afficher());
      ui->comboBox_4->setModel(tmpmedicament->afficher());
      ui->comboBox->setModel(tmpmedicament->afficher());
      ui->comboBox_5->setModel(tmpmedicament->afficherf());
      ui->comboBox_6->setModel(tmpmedicament->afficherf());
      QMessageBox::information(nullptr, QObject::tr("Ajouter medicament"),
                        QObject::tr("medicament ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter medicament"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}


void Youssef::on_pb_modifier_medicament_clicked()
{
           QString id=ui->comboBox_4->currentText();
           QString nom = ui->lineEdit_nom_m2->text();
           QString type = ui->lineEdit_type_m2->text();
           QString prix = ui->lineEdit_prix_m2->text();
           QString maladie = ui->lineEdit_maladie_m2->text();
           QString quantite = ui->lineEdit_quantite_m2->text();
           QString nomf = ui->comboBox_6->currentText();


           Medicament med (id,nom,type,prix,maladie,quantite,nomf);

                   QSqlQuery query;

                   bool test=med.modifier();
                   if(test)
                   {

                       ui->tabmedicament->setModel(tmpmedicament->afficher());//refresh
                       ui->comboBox_5->setModel(tmpmedicament->afficherf());
                       ui->comboBox_6->setModel(tmpmedicament->afficherf());
                       QMessageBox::information(nullptr, QObject::tr("Modifier Medicament"),
                                   QObject::tr("Medicament Modifier.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

                   }
                   else
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Supprimer Medicament"),
                                   QObject::tr("Erreur !.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                   }

                   //ui->lineEdit_id_m2->clear();
                   ui->lineEdit_nom_m2->clear();
                   ui->lineEdit_type_m2->clear();
                   ui->lineEdit_prix_m2->clear();
                   ui->lineEdit_maladie_m2->clear();
                   ui->lineEdit_quantite_m2->clear();
                   ui->comboBox_6->clear();

}



void Youssef::on_pb_supprimer_nourriture_clicked()
{
   QString id = ui->comboBox_2->currentText();

            QString str = " Vous voulez vraiment supprimer \n le produit ayant pour identifiant :";
                          int ret = QMessageBox::question(this, tr("Produit"),str,QMessageBox::Ok|QMessageBox::Cancel);

                          switch (ret) {
                            case QMessageBox::Ok:
                                if (tmpnourriture->supprimer(id))
                                   { QMessageBox ::information(0, qApp->tr("Suppression"),
                                        qApp->tr("le produit a été supprimé"), QMessageBox::Ok);
                                    ui->tabnourriture->setModel(tmpnourriture->afficher());}
                                else
                                          {

                                              QMessageBox::critical(0, qApp->tr("Suppression"),
                                                  qApp->tr("produit non trouvé "), QMessageBox::Cancel);

                                          }


                              break;
                            case QMessageBox::Cancel:

                                break;
                            default:
                                // should never be reached
                                break;
                          }

    ui->comboBox_2->setModel(tmpnourriture->afficher());
    ui->comboBox_3->setModel(tmpnourriture->afficher());


}

void Youssef::on_pb_modifier_nourriture_clicked()
{
    QString id=ui->comboBox_3->currentText();
    QString nom = ui->lineEdit_nom_n2_2->text();
    QString type = ui->lineEdit_type_n2_2->text();
    QString prix = ui->lineEdit_prix_n2_2->text();
    QString valid = ui->lineEdit_valid_n2_2->text();
    QString nomf= ui->comboBox_fournisseur1->currentText();



    Nourriture nourr (id,nom,type,prix,valid,nomf);

            QSqlQuery query;

            bool test=nourr.modifier();
            if(test)
            {

                ui->tabnourriture->setModel(tmpnourriture->afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Modifier Nourriture"),
                            QObject::tr("Nourriture Modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer Nourriture"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }


            //ui->lineEdit_id_n2_2->clear();
            ui->lineEdit_nom_n2_2->clear();
            ui->lineEdit_type_n2_2->clear();
            ui->lineEdit_prix_n2_2->clear();
            ui->lineEdit_valid_n2_2->clear();

}

void Youssef::on_pb_rechercher_medicament_clicked()
{
    QString nom = ui->lineEdit_recherche_med->text();
           ui->tabmedicament->setModel(tmpmedicament->rechercher(nom));
}

void Youssef::on_pb_trier_nourriture_clicked()
{
    ui->tabnourriture->setModel(tmpnourriture->trier());
}

void Youssef::on_pb_pdf_medicament_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
    QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfMedicaments.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des Medicaments");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 15));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"ID");
                   painter.drawText(1400,3300,"NOM");
                   painter.drawText(2600,3300,"TYPE");
                   painter.drawText(3800,3300,"PRIX");
                   painter.drawText(5000,3300,"MALADIE");
                   painter.drawText(6200,3300,"QUANTITE");
                   painter.drawText(7400,3300,"NOMF");
                   QSqlQuery query;
                   query.prepare("select * from MEDICAMENT");
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
                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {

                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }

}

void Youssef::on_pb_pdf_nourriture_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
        //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
    QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfNourritures.pdf");
               QPainter painter(&pdf);
              int i = 4000;
                   painter.setPen(Qt::blue);
                   painter.setFont(QFont("Arial", 30));
                   painter.drawText(1100,1200,"Liste Des Nourritures");
                   painter.setPen(Qt::black);
                   painter.setFont(QFont("Arial", 15));
                  // painter.drawText(1100,2000,afficheDC);
                   painter.drawRect(100,100,7300,2600);
                   //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                   painter.drawRect(0,3000,9600,500);
                   painter.setFont(QFont("Arial", 9));
                   painter.drawText(200,3300,"ID");
                   painter.drawText(1600,3300,"NOM");
                   painter.drawText(2100,3300,"TYPE");
                   painter.drawText(3200,3300,"PRIX");
                   painter.drawText(5300,3300,"VALID");
                   painter.drawText(7400,3300,"IDF");


                   QSqlQuery query;
                   query.prepare("select * from NOURRITURE");
                   query.exec();
                   while (query.next())
                   {
                       painter.drawText(200,i,query.value(0).toString());
                       painter.drawText(1300,i,query.value(1).toString());
                       painter.drawText(2100,i,query.value(2).toString());
                       painter.drawText(3200,i,query.value(3).toString());
                       painter.drawText(5300,i,query.value(4).toString());
                       painter.drawText(7400,i,query.value(5).toString());



                      i = i + 500;
                   }
                   int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                       if (reponse == QMessageBox::Yes)
                       {

                           painter.end();
                       }
                       if (reponse == QMessageBox::No)
                       {
                            painter.end();
                       }

}



void Youssef::on_pb_supprimer_medicament_clicked()
{
    QString id = ui->comboBox->currentText();

            QString str = " Vous voulez vraiment supprimer \n le produit ayant pour identifiant :";
                          int ret = QMessageBox::question(this, tr("Produit"),str,QMessageBox::Ok|QMessageBox::Cancel);

                          switch (ret) {
                            case QMessageBox::Ok:
                                if (tmpmedicament->supprimer(id))
                                {QMessageBox ::information(0, qApp->tr("Suppression"),
                                    qApp->tr("le produit a été supprimé"), QMessageBox::Ok);
                                    ui->tabmedicament->setModel(tmpmedicament->afficher());
                                ui->comboBox_5->setModel(tmpmedicament->afficherf());
                                 ui->comboBox_6->setModel(tmpmedicament->afficherf());
                                }
                                else
                                          {

                                              QMessageBox::critical(0, qApp->tr("Suppression"),
                                                  qApp->tr("produit non trouvé "), QMessageBox::Cancel);

                                          }


                              break;
                            case QMessageBox::Cancel:

                                break;
                            default:
                                // should never be reached
                                break;
                          }

ui->comboBox->setModel(tmpmedicament->afficher());
ui->comboBox_5->setModel(tmpmedicament->afficherf());
ui->comboBox_6->setModel(tmpmedicament->afficherf());
}


void Youssef::on_pb_confirmer_nourr_clicked(){
    QString id=ui->comboBox_3->currentText();
          QSqlQuery query;
          query.prepare("select * from NOURRITURE where ID='"+id+"'");
          if (query.exec())
          {
           while (query.next())
           {    //ui->comboBox_3->setModel(tmpnourriture->afficher());


               ui->lineEdit_nom_n2_2->setText(query.value(1).toString());
               ui->lineEdit_type_n2_2->setText(query.value(2).toString());
               ui->lineEdit_prix_n2_2->setText(query.value(3).toString());
               ui->lineEdit_valid_n2_2->setText(query.value(4).toString());







}}}


void Youssef::on_pb_confirmer_medicament_clicked()
{
    QString id=ui->comboBox_4->currentText();
          QSqlQuery query;
          query.prepare("select * from MEDICAMENT where ID='"+id+"'");
          if (query.exec())
          {
           while (query.next())
           {    //ui->comboBox_4->setModel(tmpmedicament->afficher());



               ui->lineEdit_nom_m2->setText(query.value(1).toString());
               ui->lineEdit_type_m2->setText(query.value(2).toString());
               ui->lineEdit_prix_m2->setText(query.value(3).toString());
               ui->lineEdit_maladie_m2->setText(query.value(4).toString());
               ui->lineEdit_quantite_m2->setText(query.value(5).toString());
               ui->comboBox_6->setModel(tmpmedicament->afficher());






}}

}

void Youssef::on_pb_ajouter_medicament_2_clicked()
{
    ui->comboBox_5->setModel(tmpmedicament->afficherf());

}


void Youssef::on_pb_ajouter_medicament_3_clicked()
{
    ui->comboBox_6->setModel(tmpmedicament->afficherf());

}

void Youssef::on_pb_pdf_medicament_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from MEDICAMENT where QUANTITE < 5 ");
            float salaire=model->rowCount();
            model->setQuery("select * from MEDICAMENT where QUANTITE  between 5 and 10 ");
            float salairee=model->rowCount();
            model->setQuery("select * from MEDICAMENT where QUANTITE>10 ");
            float salaireee=model->rowCount();
            float total=salaire+salairee+salaireee;
            QString a=QString("moins de 5 Medicaments "+QString::number((salaire*100)/total,'f',2)+"%" );
            QString b=QString("entre 5 et 10 Medicaments "+QString::number((salairee*100)/total,'f',2)+"%" );
            QString c=QString("+10 Medicaments "+QString::number((salaireee*100)/total,'f',2)+"%" );
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
            chart->setTitle("Pourcentage Par Quantite:type  Medicaments "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();

}

void Youssef::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("farmeresprit414@gmail.com",ui->comboBox_7->currentText(), ui->subject->text(),ui->msg->toPlainText());
}
void Youssef::mailSent(QString status)
{
    if(status == "Message sent")

        N.mail_commande();
}
void Youssef::on_pb_ajouter_evenements_clicked()
{
    QString id = ui->lineEdit_id_ev->text();
    QString nom = ui->lineEdit_2_nom_ev->text();
    QString type = ui->lineEdit_3_type_ev->text();
    QString lieu = ui->lieu->text();
    QDate datee = ui->dateEdit_ev->date();


  Evenements e(id,nom,type,lieu,datee);
  bool test=e.ajouter();
  if(test)
  {   ui->tabevenements ->setModel(tmpevenements->afficher());
      ui->comboBox_8_ev->setModel(tmpevenements->afficher());
      ui->comboBox_10_ev->setModel(tmpevenements->afficher());

      QMessageBox::information(nullptr, QObject::tr("Ajouter evenements"),
                        QObject::tr("evenements ajouté.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter evenements"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}




void Youssef::on_pb_confirmer_evenements_clicked()
{
    QString id=ui->comboBox_8_ev->currentText();
          QSqlQuery query;
          query.prepare("select * from EVENEMENTS where ID='"+id+"'");
          if (query.exec())
          {
           while (query.next())
           {


               ui->lineEdit_nom_2_ev->setText(query.value(1).toString());
               ui->lineEdit_type_2_ev->setText(query.value(2).toString());
               ui->lineEdit_lieu_2->setText(query.value(3).toString());
               QDateTime datee=query.value(4).toDateTime();
                               ui->dateEdit_ev99->setDateTime(datee);








}}
}

void Youssef::on_pb_modifier_evenements_clicked()
{

    QString id=ui->comboBox_8_ev->currentText();
    QString nom = ui->lineEdit_nom_2_ev->text();
    QString type = ui->lineEdit_type_2_ev->text();
    QString lieu = ui->lineEdit_lieu_2->text();
    QDate datee = ui->dateEdit_ev99->date();


    Evenements e (id,nom,type,lieu,datee);

            QSqlQuery query;

            bool test=e.modifier();
            if(test)
            {

                ui->tabevenements->setModel(tmpevenements->afficher());//refresh
                QMessageBox::information(nullptr, QObject::tr("Modifier Evenements"),
                            QObject::tr("Evenements Modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer Evenements"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }


            ui->lineEdit_nom_2_ev->clear();
            ui->lineEdit_type_2_ev->clear();
            ui->lineEdit_lieu_2->clear();
            ui->dateEdit_ev99->clear();
}

void Youssef::on_pb_supprimer_evenements_clicked()
{
    QString id = ui->comboBox_10_ev->currentText();
        {
            QString str = " Vous voulez vraiment supprimer \n le produit ayant pour identifiant :";
                          int ret = QMessageBox::question(this, tr("Produit"),str,QMessageBox::Ok|QMessageBox::Cancel);

                          switch (ret) {
                            case QMessageBox::Ok:
                                if (tmpevenements->supprimer(id))
                                   { ui->tabevenements->setModel(tmpevenements->afficher());
                                    ui->comboBox_10_ev->setModel(tmpevenements->afficher());

                                    QMessageBox ::information(0, qApp->tr("Suppression"),
                                    qApp->tr("l'Evenement a été supprimé"), QMessageBox::Ok);}
                                else
                                          {

                                              QMessageBox::critical(0, qApp->tr("Suppression"),
                                                  qApp->tr("Evenement non trouvé "), QMessageBox::Cancel);

                                          }


                              break;
                            case QMessageBox::Cancel:

                                break;
                            default:
                                // should never be reached
                                break;
                          }


}}

void Youssef::on_pb_rechercher_evenements_clicked()
{
    QString nom = ui->lineEdit_recherche_events->text();
           ui->tabevenements->setModel(tmpevenements->rechercher(nom));
}



void Youssef::on_pb_trier_evenements_clicked()
{
     ui->tabevenements->setModel(tmpevenements->trier());
}

