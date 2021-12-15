#include "ahmed.h"
#include "ui_ahmed.h"
#include <QMessageBox>
#include "veterinaire.h"
#include "employe.h"
#include "livreur.h"
#include "connexion.h"
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "smtp.h"
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
#include <QtCharts/QBarCategoryAxis>
#include"QSortFilterProxyModel"
QT_CHARTS_USE_NAMESPACE


Ahmed::Ahmed(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Ahmed)
{
    ui->setupUi(this);
    setWindowTitle("Gestion de tous les employés");
    ui->resultats->setText("0.0");

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));

    ui->tabveterinaire->setModel(tmpveterinaire->afficher());
    ui->tabemploye->setModel(tmpemploye->afficher());
    ui->comboBox->setModel(tmpemploye->afficher_vet());
    ui->comboBox_l->setModel(tmpemploye->afficher_livreur());
    ui->tablivreur->setModel(tmplivreur->afficher());
    ui->rcpt->setModel(tmpemploye->afficher1());
    ui->voiture->setModel(tmplivreur->affichervoiture());
    ui->voiture2->setModel(tmplivreur->affichervoiture());
    ui->comboBox_4->setModel(tmpveterinaire->afficher());
    ui->comboBox_3->setModel(tmpveterinaire->afficher());
    ui->comboBox_11->setModel(tmpemploye->afficher());
    ui->comboBox_12->setModel(tmpemploye->afficher());
    ui->comboBox_30->setModel(tmplivreur->afficher());
    ui->comboBox_40->setModel(tmplivreur->afficher());








}

Ahmed::~Ahmed()
{
    delete ui;
}


void Ahmed::on_pb_ajouter_veterinaire_clicked()
{
        QString id = ui->comboBox->currentText();
        QString nom = ui->lineEdit_nomv->text();
        QString prenom = ui->lineEdit_prenomv->text();
        QString specialite = ui->lineEdit_specialite->text();
        QDate diplome = ui->lineEdit_diplome->date();
        int exp = ui->lineEdit_exp->text().toInt();
        QString mail = ui->lineEdit_mailv->text();


        Veterinaire v(id,nom,prenom,specialite,diplome,exp,mail);

        if (ui->lineEdit_specialite->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP specialité!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
                else if (ui->lineEdit_exp->text().isEmpty())
                 {

                     QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP experience!!!!") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
                 }
        else if (testmail(ui->lineEdit_mailv->text())==false)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Votre Adresse Mail!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
      }

        else {

            bool test=v.ajouter();

      notifier = new QSystemTrayIcon(this);
      //notifier = new QSystemTrayIcon(this);
          notifier->setIcon(QIcon(":/add.png"));
          notifier->show();
      if(test)
      { ui->tabveterinaire->setModel(tmpveterinaire->afficher());
            ui->comboBox_3->setModel(tmpveterinaire->afficher());
            ui->comboBox_4->setModel(tmpveterinaire->afficher());
            ui->comboBox->setModel(tmpemploye->afficher_vet());

            notifier->showMessage("Notification","Nouveau Veterinaire ajoute",QSystemTrayIcon::Warning,10000);
      }
        }
}

void Ahmed::on_pb_confirmer_clicked(){
    QString id = ui->comboBox->currentText();

    QSqlQuery query;
            query.prepare("SELECT * FROM EMPLOYE WHERE ID='"+id+"'");
            if(query.exec())
            {
                while(query.next())
                {   ui->lineEdit_nomv->setText(query.value(1).toString());
                    ui->lineEdit_prenomv->setText(query.value(2).toString());
                    ui->lineEdit_mailv->setText(query.value(5).toString());

                }

            }
            else
            {
                QObject::tr("ERREUR");
            }


}


void Ahmed::on_pb_ajouter_employe_clicked()
{


    QString id = ui->lineEdit_id_2->text();
    QString nom = ui->lineEdit_nome->text();
    QString prenom = ui->lineEdit_prenome->text();
    QString fonction = ui->lineEdit_fonctione->text();
    int salaire = ui->lineEdit_salairee->text().toInt();
    QString mail = ui->lineEdit_maile->text();

  Employe em (id,nom,prenom,fonction,salaire,mail);

  if (ui->lineEdit_id_2->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
   }
          else if (ui->lineEdit_nome->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP nom!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }

  else if (ui->lineEdit_prenome->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP prenom!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }

  else if (ui->lineEdit_fonctione->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP fonction!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }

  else if (ui->lineEdit_salairee->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP salaire!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }

  else if (testmail(ui->lineEdit_maile->text())==false)
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Votre Adresse Mail!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
}


  else {

  bool test=em.ajouter();

  notifier = new QSystemTrayIcon(this);
  //notifier = new QSystemTrayIcon(this);
      notifier->setIcon(QIcon(":/add.png"));
      notifier->show();

  if(test)
  { ui->tabemploye ->setModel(tmpemploye->afficher());
       ui->comboBox_11->setModel(tmpemploye->afficher());
       ui->comboBox_12->setModel(tmpemploye->afficher());
       ui->comboBox->setModel(tmpemploye->afficher_vet());
       ui->comboBox_l->setModel(tmpemploye->afficher_livreur());
       ui->rcpt->setModel(tmpemploye->afficher1());



       notifier->showMessage("Notification","Nouveau Employe ajouté",QSystemTrayIcon::Warning,60000);
  }
  }
}

void Ahmed::on_pb_supprimer_employe_clicked()
{
    QString id=ui->comboBox_11->currentText();
    bool test=tmpemploye->supprimer(id);
    if(test)
    {
        ui->tabemploye->setModel(tmpemploye->afficher());//refresh
        ui->comboBox_11->setModel(tmpemploye->afficher());
        ui->comboBox->setModel(tmpemploye->afficher_vet());
        ui->comboBox_l->setModel(tmpemploye->afficher_livreur());

        QMessageBox::information(nullptr, QObject::tr("Supprimer employe"),
                    QObject::tr("employe supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer employe"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void Ahmed::on_pb_modifier_employe_clicked()
{
           QString id=ui->comboBox_12->currentText();
           QString nom = ui->lineEdit_nom2e->text();
           QString prenom = ui->lineEdit_prenom2e->text();
           QString fonction = ui->lineEdit_fonction2e->text();
           int salaire = ui->lineEdit_salaire2e->text().toInt();
           QString mail = ui->lineEdit_maile2->text();


           Employe emp (id,nom,prenom,fonction,salaire,mail);

                   QSqlQuery query;

                   bool test=emp.modifier();
                   if(test)
                   {

                       ui->tabemploye->setModel(tmpemploye->afficher());//refresh
                       ui->comboBox_12->setModel(tmpemploye->afficher());
                       ui->comboBox->setModel(tmpemploye->afficher_vet());
                       ui->comboBox_l->setModel(tmpemploye->afficher_livreur());
                       ui->rcpt->setModel(tmpemploye->afficher1());




                       QMessageBox::information(nullptr, QObject::tr("Modifier employe"),
                                   QObject::tr("employe Modifier.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

                   }
                   else
                   {
                       QMessageBox::critical(nullptr, QObject::tr("Modifier employé"),
                                   QObject::tr("Erreur !.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
                   }

                   ui->lineEdit_nom2e->clear();
                   ui->lineEdit_prenom2e->clear();
                   ui->lineEdit_fonction2e->clear();
                   ui->lineEdit_salaire2e->clear();
                   ui->lineEdit_maile2->clear();


}



void Ahmed::on_pb_supprimer_veterinaire_clicked()
{
    QString id=ui->comboBox_3->currentText();
    bool test=tmpveterinaire->supprimer(id);
    if(test)
    {
        ui->tabveterinaire->setModel(tmpveterinaire->afficher());//refresh
        ui->comboBox_3->setModel(tmpveterinaire->afficher());
        ui->comboBox_4->setModel(tmpveterinaire->afficher());



        QMessageBox::information(nullptr, QObject::tr("Supprimer veterinaire"),
                    QObject::tr("veterinaire supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer veterinaire"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ahmed::on_pb_modifier_veterinaire_clicked()
{
    QString id=ui->comboBox_4->currentText();
    QString nom = ui->lineEdit_nomv2->text();
    QString prenom = ui->lineEdit_prenomv2->text();
    QString specialite = ui->lineEdit_specialitev2->text();
    QDate diplome = ui->lineEdit_diplomev2->date();
    int exp = ui->lineEdit_expv2->text().toInt();
    QString mail = ui->lineEdit_mailv2->text();




    Veterinaire vet (id,nom,prenom,specialite,diplome,exp,mail);

            QSqlQuery query;

            bool test=vet.modifier();
            if(test)
            {

                ui->tabveterinaire->setModel(tmpveterinaire->afficher());//refresh
                ui->comboBox_4->setModel(tmpveterinaire->afficher());
                QMessageBox::information(nullptr, QObject::tr("Modifier veterinaire"),
                            QObject::tr("veterinaire Modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer veterinaire"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }


            ui->lineEdit_nomv2->clear();
            ui->lineEdit_prenomv2->clear();
            ui->lineEdit_specialitev2->clear();
            ui->lineEdit_diplomev2->clear();
            ui->lineEdit_expv2->clear();
            ui->lineEdit_mailv2->clear();


}


 void Ahmed::on_pb_pushbutton_tri_clicked()
 {
     ui->tabveterinaire->setModel(tmpveterinaire->triveterinaire());
 }

 void Ahmed::on_pushbutton_tri1_clicked()
 {
     ui->tabemploye->setModel(tmpemploye->triemploye());
 }

 void Ahmed::on_pb_pushbutton_pdf_clicked(){
     //QDateTime datecreation = date.currentDateTime();
     //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
     QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfEmploye.pdf");
            QPainter painter(&pdf);
           int i = 4000;
                painter.setPen(Qt::blue);
                painter.setFont(QFont("Arial", 30));
                painter.drawText(1100,1200,"Liste Des Employes");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Arial", 50));
               // painter.drawText(1100,2000,afficheDC);
                painter.drawRect(100,100,7300,2600);
                //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
                painter.drawRect(0,3000,9600,500);
                painter.setFont(QFont("Arial", 9));
                painter.drawText(200,3300,"ID");
                painter.drawText(1700,3300,"NOM");
                painter.drawText(3200,3300,"PRENOM");
                painter.drawText(4900,3300,"FONCTION");
                painter.drawText(6600,3300,"SALAIRE");
                painter.drawText(8300,3300,"Mail");

                QSqlQuery query;
                query.prepare("select * from EMPLOYE");
                query.exec();
                while (query.next())
                {
                    painter.drawText(200,i,query.value(0).toString());
                    painter.drawText(1700,i,query.value(1).toString());
                    painter.drawText(3200,i,query.value(2).toString());
                    painter.drawText(4900,i,query.value(3).toString());
                    painter.drawText(6600,i,query.value(4).toString());
                    painter.drawText(8300,i,query.value(5).toString());
                   i = i + 700;
                }
                int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                    if (reponse == QMessageBox::Yes)
                    {
                        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfEmploye.pdf"));
                        painter.end();
                    }
                    if (reponse == QMessageBox::No)
                    {
                         painter.end();
                    }
 }

void Ahmed::on_pushbutton_rechercher1_clicked()
{

    QString nom = ui->lineEdit_rechercher11->text();
    ui->tabveterinaire->setModel(tmpveterinaire->rechercher1(nom));
}


void Ahmed::on_pushbutton_rechercher_clicked()
{
    QString nom = ui->lineEdit_rechercher->text();
    ui->tabemploye->setModel(tmpemploye->rechercher(nom));
}


void Ahmed::sendMail()
{
    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919", "smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("farmeresprit414@gmail.com", ui->rcpt->currentText() , ui->subject->text(),ui->msg->toPlainText());
}

void Ahmed::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_commande();
}

void Ahmed::on_pushbutton_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from employe where salaire < 1000 ");
        float salaire=model->rowCount();
        model->setQuery("select * from employe where salaire between 1000 and 5000 ");
        float salairee=model->rowCount();
        model->setQuery("select * from employe where salaire>5000 ");
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

void Ahmed::on_pb_ajouter_livreur_clicked()
{
        QString id = ui->comboBox_l->currentText();
        QString nom = ui->lineEdit_noml->text();
        QString prenom = ui->lineEdit_prenoml->text();
        QString tel = ui->lineEdit_tell->text();
        int exp = ui->lineEdit_expl->text().toInt();
        QString mail = ui->lineEdit_maill->text();
        QString voiture = ui->voiture->currentText();



       Livreur l1(id,nom,prenom,tel,exp,mail,voiture);

        if (ui->lineEdit_tell->text().isEmpty())
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Telephone!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

         }
                else if (ui->lineEdit_expl->text().isEmpty())
                 {

                     QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP experience!!!!") ;
                     QMessageBox::critical(0, qApp->tr("Ajout"),

                                     qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
        }
        else if (testmail(ui->lineEdit_maill->text())==false)
         {

             QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Votre Adresse Mail!!!!") ;
             QMessageBox::critical(0, qApp->tr("Ajout"),

                             qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
      }



        else {

      bool test=l1.ajouter();

      notifier = new QSystemTrayIcon(this);
      //notifier = new QSystemTrayIcon(this);
          notifier->setIcon(QIcon(":/add.png"));
          notifier->show();

      if(test)
      {
            ui->tablivreur->setModel(tmplivreur->afficher());
            ui->comboBox_40->setModel(tmplivreur->afficher());
            ui->comboBox_30->setModel(tmplivreur->afficher());
            ui->comboBox_l->setModel(tmpemploye->afficher_livreur());
            ui->rcpt->setModel(tmpemploye->afficher1());

          notifier->showMessage("Notification","Nouveau livreur ajouté",QSystemTrayIcon::Warning,10000);
      }
        }
}

void Ahmed::on_pb_confirmer1_clicked(){
    QString id = ui->comboBox_l->currentText();

    QSqlQuery query;
            query.prepare("SELECT * FROM EMPLOYE WHERE ID='"+id+"'");
            if(query.exec())
            {
                while(query.next())
                {   ui->lineEdit_noml->setText(query.value(1).toString());
                    ui->lineEdit_prenoml->setText(query.value(2).toString());
                    ui->lineEdit_maill->setText(query.value(5).toString());

                }

            }
            else
            {
                QObject::tr("ERREUR");
            }
}

void Ahmed::on_pb_supprimer_livreur_clicked()
{
    QString id=ui->comboBox_30->currentText();
    bool test=tmplivreur->supprimer(id);
    if(test)
    {ui->tablivreur->setModel(tmplivreur->afficher());//refresh
        ui->comboBox_30->setModel(tmplivreur->afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer livreur"),
                    QObject::tr("livreur supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer livreur"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Ahmed::on_pb_modifier_livreur_clicked()
{
    QString id=ui->comboBox_40->currentText();
    QString nom = ui->lineEdit_noml2->text();
    QString prenom = ui->lineEdit_prenoml2->text();
    QString tel = ui->lineEdit_tell2->text();
    int exp = ui->lineEdit_expl2->text().toInt();
    QString mail = ui->lineEdit_maill2->text();
    QString voiture = ui->voiture2->currentText();





    Livreur ll (id,nom,prenom,tel,exp,mail,voiture);

            QSqlQuery query;

            bool test=ll.modifier();
            if(test)
            {

                ui->tablivreur->setModel(tmplivreur->afficher());//refresh
                ui->comboBox_40->setModel(tmplivreur->afficher());
                QMessageBox::information(nullptr, QObject::tr("Modifier livreur"),
                            QObject::tr("livreur Modifier.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Supprimer livreur"),
                            QObject::tr("Erreur !.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
            }


            ui->lineEdit_noml2->clear();
            ui->lineEdit_prenoml2->clear();
            ui->lineEdit_tell2->clear();
            ui->lineEdit_expl2->clear();
            ui->lineEdit_maill2->clear();
            ui->lineEdit_maill2->clear();

}


 void Ahmed::on_pb_pushbutton_tri2_clicked()
 {
     ui->tablivreur->setModel(tmplivreur->trilivreur());
 }

 void Ahmed::on_pb_confirmer98_clicked(){
     QString id=ui->comboBox_4->currentText();
           QSqlQuery query;
           query.prepare("select * from VETERINAIRE where ID='"+id+"'");
           if (query.exec())
           {
            while (query.next())
            {    //ui->comboBox_4->setModel(tmpveterinaire->afficher());


                ui->lineEdit_nomv2->setText(query.value(1).toString());
                ui->lineEdit_prenomv2->setText(query.value(2).toString());
                ui->lineEdit_specialitev2->setText(query.value(3).toString());
                ui->lineEdit_diplomev2->setDate(query.value(4).toDate());
                ui->lineEdit_expv2->setText(query.value(5).toString());
                ui->lineEdit_mailv2->setText(query.value(6).toString());
            }
           }
 }


 void Ahmed::on_pb_confirmer99_clicked()
 {
     QString id=ui->comboBox_40->currentText();
           QSqlQuery query;
           query.prepare("select * from LIVREUR where ID='"+id+"'");
           if (query.exec())
           {
            while (query.next())
            {    //ui->comboBox_40->setModel(tmplivreur->afficher());


                ui->lineEdit_noml2->setText(query.value(1).toString());
                ui->lineEdit_prenoml2->setText(query.value(2).toString());
                ui->lineEdit_tell2->setText(query.value(3).toString());
                ui->lineEdit_expl2->setText(query.value(4).toString());
                ui->lineEdit_maill2->setText(query.value(5).toString());

            }
           }
 }


 void Ahmed::on_pb_confirmer97_clicked()
 {
     QString id=ui->comboBox_12->currentText();
           QSqlQuery query;
           query.prepare("select * from EMPLOYE where ID='"+id+"'");
           if (query.exec())
           {
            while (query.next())
            {    //ui->comboBox_12->setModel(tmpemploye->afficher());


                ui->lineEdit_nom2e->setText(query.value(1).toString());
                ui->lineEdit_prenom2e->setText(query.value(2).toString());
                ui->lineEdit_fonction2e->setText(query.value(3).toString());
                ui->lineEdit_salaire2e->setText(query.value(4).toString());
                ui->lineEdit_maile2->setText(query.value(5).toString());
            }
           }
 }

 void Ahmed::on_pushbutton_rechercher2_clicked()
 {
     QString nom = ui->lineEdit_rechercher84->text();
     ui->tablivreur->setModel(tmplivreur->rechercher2(nom));
 }

void Ahmed::on_plus_clicked()
{
    ui->resultats->setText(QString::number(ui->n1->value() + ui->n2->value()));
}

void Ahmed::on_moins_clicked()
{
    ui->resultats->setText(QString::number(ui->n1->value() - ui->n2->value()));

}

void Ahmed::on_fois_clicked()
{
    ui->resultats->setText(QString::number(ui->n1->value() * ui->n2->value()));

}

void Ahmed::on_sur_clicked()
{
    ui->resultats->setText(QString::number(ui->n1->value() / ui->n2->value()));

}

void Ahmed::on_actionNouveau_triggered()
{
        currentFile.clear();
        ui->textEdit99->setText(QString());
}

void Ahmed::on_actionEnregistrer_triggered()
{
       QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer sous..");
       QFile file(fileName);
       if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "probléme", "Pas d'enregistrement de fichier" + file.errorString());
           return;
       }
       currentFile = fileName;
       setWindowTitle(fileName);
       QTextStream out(&file);
       QString text = ui->textEdit99->toPlainText();
       out << text;
       file.close();
}

void Ahmed::on_actionQuitter_triggered()
{
    close();
}

void Ahmed::on_actionCopier_triggered()
{
    ui->textEdit99->copy();
}

void Ahmed::on_actionColler_triggered()
{
    ui->textEdit99->paste();
}

void Ahmed::on_actionCoper_triggered()
{
    ui->textEdit99->cut();

}

void Ahmed::on_actionOuvrir_triggered()
{
        QString fileName = QFileDialog::getOpenFileName(this, "Ouvrir le fichier");
        QFile file(fileName);
        currentFile = fileName;
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Probléme", "fichier non ouvrir " + file.errorString());
            return;
        }
        setWindowTitle(fileName);
        QTextStream in(&file);
        QString text = in.readAll();
        ui->textEdit99->setText(text);
        file.close();
}

void Ahmed::on_actionImprimer_triggered()
{
       QPrinter printer;

       printer.setPrinterName("Nom de l'imprimente");
       QPrintDialog pDialog(&printer, this);
       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Probleme", "Pas de connexion avec l'imprimente");
           return;
       }
       ui->textEdit99->print(&printer);
}

void Ahmed::on_pb_pushbutton_pdf_2_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
           QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfVeterinaires.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des Véterinaire");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"ID");
               painter.drawText(1400,3300,"NOM");
               painter.drawText(2600,3300,"PRENOM");
               painter.drawText(3800,3300,"SPECIALITE");
               painter.drawText(5000,3300,"DIPLOME");
               painter.drawText(6200,3300,"EXP");
               painter.drawText(7400,3300,"Mail");


               QSqlQuery query;
               query.prepare("select * from VETERINAIRE");
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
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfVeterinaires.pdf"));
                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }
}

void Ahmed::on_pb_pushbutton_pdf_3_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
    QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfLivreurs.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des Livreur");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"ID");
               painter.drawText(1400,3300,"NOM");
               painter.drawText(2600,3300,"PRENOM");
               painter.drawText(3800,3300,"TEL");
               painter.drawText(5000,3300,"EXP");
               painter.drawText(6200,3300,"MAIL");
               painter.drawText(7400,3300,"Voiture");


               QSqlQuery query;
               query.prepare("select * from LIVREUR");
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
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfLivreurs.pdf"));
                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }
}

void Ahmed::on_pushbutton_stat_2_clicked()
{
        QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from veterinaire where exp < 5 ");
            float exp=model->rowCount();
            model->setQuery("select * from veterinaire where exp between 5 and 10 ");
            float expp=model->rowCount();
            model->setQuery("select * from veterinaire where exp>15 ");
            float exppp=model->rowCount();
            float total=exp+expp+exppp;
            QString a=QString("moins de 5 "+QString::number((exp*100)/total,'f',2)+"%" );
            QString b=QString("entre 5 et 10 "+QString::number((expp*100)/total,'f',2)+"%" );
            QString c=QString("+10ans "+QString::number((exppp*100)/total,'f',2)+"%" );
            QPieSeries *series = new QPieSeries();
            series->append(a,exp);
            series->append(b,expp);
             series->append(c,exppp);
    if (exp!=0)
    {QPieSlice *slice = series->slices().at(0);
     slice->setLabelVisible();
     slice->setPen(QPen());}
    if ( expp!=0)
    {
             // Add label, explode and define brush for 2nd slice
             QPieSlice *slice1 = series->slices().at(1);
             //slice1->setExploded();
             slice1->setLabelVisible();
    }
    if(exppp!=0)
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
            chart->setTitle("Pourcentage Par Experience:totale de "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
    }


void Ahmed::on_pushbutton_stat_3_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from livreur where exp < 5 ");
        float exp=model->rowCount();
        model->setQuery("select * from livreur where exp between 5 and 10 ");
        float expp=model->rowCount();
        model->setQuery("select * from livreur where exp>15 ");
        float exppp=model->rowCount();
        float total=exp+expp+exppp;
        QString a=QString("moins de 5 "+QString::number((exp*100)/total,'f',2)+"%" );
        QString b=QString("entre 5 et 10 "+QString::number((expp*100)/total,'f',2)+"%" );
        QString c=QString("+10ans "+QString::number((exppp*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,exp);
        series->append(b,expp);
         series->append(c,exppp);
if (exp!=0)
{QPieSlice *slice = series->slices().at(0);
 slice->setLabelVisible();
 slice->setPen(QPen());}
if ( expp!=0)
{
         // Add label, explode and define brush for 2nd slice
         QPieSlice *slice1 = series->slices().at(1);
         //slice1->setExploded();
         slice1->setLabelVisible();
}
if(exppp!=0)
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
        chart->setTitle("Pourcentage Par Experience:totale de "+ QString::number(total));
        chart->legend()->hide();
        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->resize(1000,500);
        chartView->show();

}
bool Ahmed::testmail(QString mail){
    int test=0;
    for(int i = 0; i < mail.size(); i++) {
if(mail[i]=="@")
    test++;
    }
    for(int i = 0; i < mail.size(); i++) {
if((test==1)&&(mail[i]=="."))
        return true;
    }
return false;}









