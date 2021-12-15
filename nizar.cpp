#include "nizar.h"
#include "ui_nizar.h"
#include "client.h"
#include "reclamation.h"
#include <QMessageBox>
#include<QDate>
#include<QDateEdit>
#include <QPainter>
#include <QPdfWriter>
#include "smtp.h"



Nizar::Nizar(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Nizar)
{

    ui->setupUi(this);

    ui->tabclient_reclamation->setModel(tmpclient.afficherC());
    ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
    ui->comboBox->setModel(tmpclient.afficher());
    ui->comboBox_2->setModel(tmpclient.afficher());
    ui->comboBox_3->setModel(tmpreclamation.afficher_reclamation());
    ui->comboBox_4->setModel(tmpreclamation.afficher_reclamation());//refresh



    ui->tabclient->setModel(tmpclient.afficher());
    ui->tabreclamation->setModel(tmpreclamation.afficher_reclamation());

    ui->comboBox_rcpt->setModel(tmpclient.afficherMail());



}

Nizar::~Nizar()
{
    delete ui;
}


void Nizar::on_ajouterclient_clicked()
{

    QString cin = ui->le_cin->text();
    long tel = ui->le_telephone->text().toLong();
    QString nom= ui->le_nom->text();
    QString prenom= ui->le_prenom->text();
    QString lieu= ui->Le_lieu->text();
    QString mail= ui->Mail->text();


  client c(cin,tel,nom,prenom,lieu,mail);
  bool test=c.ajouter();
  if(test)
{ui->tabclient->setModel(tmpclient.afficher());//refresh
      ui->comboBox->setModel(tmpclient.afficher());
      ui->comboBox_2->setModel(tmpclient.afficher());
      ui->tabclient_reclamation->setModel(tmpclient.afficherC());
      ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
      ui->comboBox_rcpt->setModel(tmpclient.afficherMail());

QMessageBox::information(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("client ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else if (testmail(ui->Mail->text())==false)
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Votre Adresse Mail!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);
}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}


void Nizar::on_supprimerclient_clicked()
{
    QString cin=ui->comboBox->currentText();
    bool test=tmpclient.supprimer(cin);
    if(test)
    {ui->tabclient->setModel(tmpclient.afficher());//refresh
        ui->comboBox->setModel(tmpclient.afficher());
        ui->comboBox_2->setModel(tmpclient.afficher());
        ui->tabclient_reclamation->setModel(tmpclient.afficherC());
        ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
        ui->comboBox_rcpt->setModel(tmpclient.afficherMail());

        QMessageBox::information(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("client supprimé.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer un client"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void Nizar::on_ajouterreclamation_clicked()
{
    QString code = ui->le_code_2->text();
    QString cin = ui->le_cin_c_2->text();

    QDate date_creation= ui->le_date_2->date();
  reclamation ct(code,cin,date_creation);
  bool test=ct.ajouter_reclamation();
  if(test)
{ui->tabreclamation->setModel(tmpreclamation.afficher_reclamation());//refresh
      ui->comboBox_3->setModel(tmpreclamation.afficher_reclamation());
      ui->comboBox_4->setModel(tmpreclamation.afficher_reclamation());//refresh
      ui->tabclient_reclamation->setModel(tmpclient.afficherC());
      ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
QMessageBox::information(nullptr, QObject::tr("Ajouter une reclamation"),
                  QObject::tr("reclamation ajoutée.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

}
  else
      QMessageBox::critical(nullptr, QObject::tr("Ajouter une reclamation"),
                  QObject::tr("Erreur !.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}

void Nizar::on_supprimerreclamation_clicked()
{
    QString code=ui->comboBox_3->currentText();

    bool test=tmpreclamation.supprimer_reclamation(code);
    if(test)
    {ui->tabreclamation->setModel(tmpreclamation.afficher_reclamation());
        ui->comboBox_3->setModel(tmpreclamation.afficher_reclamation());
        ui->comboBox_4->setModel(tmpreclamation.afficher_reclamation());//refresh
        ui->tabclient_reclamation->setModel(tmpclient.afficherC());
        ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
        ui->tabclient->setModel(tmpclient.afficher());
        QMessageBox::information(nullptr, QObject::tr("Supprimer une reclamation"),
                    QObject::tr("reclamation supprimée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Supprimer une reclamation"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}



void Nizar::on_modifierclient_clicked()
{
            QString cin=ui->comboBox_2->currentText();
            long tel = ui->le_telephone_2->text().toLong();
        QString nom= ui->le_nom_2->text();
        QString prenom= ui->le_prenom_2->text();
        QString lieu= ui->Lieu2->text();
        QString mail= ui->mail2->text();

        client c1;

            if(c1.rech(cin)){
                bool test = c1.modifier(cin,tel,nom,prenom);
                if(test){
                    ui->tabclient->setModel(tmpclient.afficher());
                        ui->comboBox->setModel(tmpclient.afficher());
                        ui->comboBox_2->setModel(tmpclient.afficher());
                        ui->tabclient_reclamation->setModel(tmpclient.afficherC());
                        ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
                        ui->comboBox_rcpt->setModel(tmpclient.afficherMail());



                    QMessageBox::information(nullptr, QObject::tr("Modifier un client"),
                                QObject::tr("client modifié.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier un client"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
            }

}

void Nizar::on_modifierreclamation_clicked()
{
    QString code=ui->comboBox_4->currentText();
    QDate date_creation= ui->le_date->date();

        reclamation ct;

            if(ct.rech(code)){
                bool test = ct.modifier(code,date_creation);
                if(test){
                    ui->tabreclamation->setModel(tmpreclamation.afficher_reclamation());
                    ui->comboBox_3->setModel(tmpreclamation.afficher_reclamation());
                    ui->comboBox_4->setModel(tmpreclamation.afficher_reclamation());//refresh
                    ui->tabclient_reclamation->setModel(tmpclient.afficherC());
                    ui->tabclient_reclamation2->setModel(tmpclient.afficherR());
                    QMessageBox::information(nullptr, QObject::tr("Modifier une reclamation"),
                                QObject::tr("reclamation modifiée.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
                }
                else
                    QMessageBox::critical(nullptr, QObject::tr("Modifier une reclamation"),
                                QObject::tr("Erreur !.\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);
            }
}
void Nizar::on_trierreclamation_clicked()
{
   {ui->tabreclamation->setModel(tmpreclamation.trierreclamation_code());

}

}
void Nizar::on_PDF_clicked()
{
//QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
    QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfClients.pdf");

           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(1100,1200,"Liste Des Clients");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 15));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(100,100,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(200,3300,"Cin");
               painter.drawText(1300,3300,"Telephone");
               painter.drawText(2100,3300,"Nom");
               painter.drawText(3200,3300,"Prénom");

               QSqlQuery query;
               query.prepare("select * from client");
               query.exec();
               while (query.next())
               {
                   painter.drawText(200,i,query.value(0).toString());
                   painter.drawText(1300,i,query.value(1).toString());
                   painter.drawText(2200,i,query.value(2).toString());
                   painter.drawText(3200,i,query.value(3).toString());
                   painter.drawText(4500,i,query.value(4).toString());
                   painter.drawText(7700,i,query.value(5).toString());
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



                void Nizar::on_trierclient_clicked()
                {
{ ui->tabclient->setModel(tmpclient.trier_cin());
                }

}




void Nizar::on_cherch_code_textChanged()
{
    QString code=ui->cherch_code->text();
    ui->tabreclamation->setModel(tmpreclamation.Rechercher(code));
}




void Nizar::on_sendbtn_clicked()
{

    Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("farmeresprit414@gmail.com",ui->comboBox_rcpt->currentText(), ui->subject->text(),ui->msg->toPlainText());
}
void Nizar::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_commande();
}
bool Nizar::testmail(QString mail){
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

void Nizar::on_modifierclient_2_clicked()
{
    QString id=ui->comboBox_2->currentText();
          QSqlQuery query;
          query.prepare("select * from CLIENT where CIN='"+id+"'");
          if (query.exec())
          {
           while (query.next())
           {    //ui->comboBox_12->setModel(tmpemploye->afficher());


               ui->le_telephone_2->setText(query.value(1).toString());
               ui->le_prenom_2->setText(query.value(2).toString());
               ui->le_nom_2->setText(query.value(3).toString());
               ui->Lieu2->setText(query.value(4).toString());
               ui->mail2->setText(query.value(5).toString());
           }
          }
}
