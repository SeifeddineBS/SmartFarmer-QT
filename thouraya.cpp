#include "thouraya.h"
#include "ui_thouraya.h"


//#include "ui_mainwindow.h"
#include<QDate>
#include<QMessageBox>
#include<QSystemTrayIcon>
#include "maintenance.h"
#include "connexion.h"
#include "materiel.h"
#include<QDebug>
#include<QDesktopServices>

Thou::Thou(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Thou)
{
    ui->setupUi(this);
    ui->tabmateriel->setModel(tmpmateriel->afficher());
    //ui->tableView->setModel(tmpmaint->afficher());
    //ui->comboBox_6->setModel(commande->afficher());
    //ui->comboBox_7->setModel(commande->afficher());
    //ui->comboBoxid->setModel(tmpmateriel->afficher());
    //ui->tabanimalc->setModel(tmpanim->afficherc());
    //ui->comboBox_4->setModel(tmpanim->afficher());
    //ui->comboBox1->setModel(tmpmateriel->afficher());
    //ui->comboBox_9->setModel(tmpanim->afficher2());
}
Thou::~Thou()
{
    delete ui;
}


void Thou::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(2);
}
void Thou::on_youssef_clicked()
{
    youss= new Youssef(this);
      youss->show();
}
void Thou::on_seif_clicked()
{
    anim= new Animal(this);
      anim->show();
}
void Thou::on_ahmed_clicked()
{
    ahm= new Ahmed(this);
      ahm->show();
}
void Thou::on_adem_clicked()
{
    sec= new SecDialog(this);
      sec->show();
}
void Thou::on_nizar_clicked()
{
    niz= new Nizar(this);
      niz->show();
}
void Thou::on_retour_clicked()
{
ui->stackedWidget->setCurrentIndex(0);
}
void Thou::on_retour2_clicked()
{
ui->stackedWidget->setCurrentIndex(0);
}


void Thou::on_pushButton_ajoutermateriel_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
       QString type = ui->lineEdit_type->text();
       QString etat = ui->lineEdit_etat->text();
       QDate dateachat = ui->dateEdit_achat->date();
      // QString maint = ui->lineEdit_maint->text();
       QString maint = ui->comboBox2->currentText();
       Materiel mat (id,type,etat,dateachat,maint);

       notifier = new QSystemTrayIcon(this);
       //notifier = new QSystemTrayIcon(this);
           notifier->setIcon(QIcon(":/notification.png"));
           notifier->show();

     if (ui->lineEdit_id->text().isEmpty())
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
             else if (ui->lineEdit_type->text().isEmpty())
              {

                  QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP type!!!!") ;
                  QMessageBox::critical(0, qApp->tr("Ajout"),

                                  qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

              }
     else if (ui->lineEdit_etat->text().isEmpty())
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP etat !!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
     else if (ui->dateEdit_achat->text().isEmpty())
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP date !!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
     //else if (ui->lineEdit_maint->text().isEmpty())
     else if (ui->comboBox2->currentText().isEmpty())
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP maintenance entrez (oui) ou (non) !!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
     else {
         bool test=mat.ajouter();
       if (test)
       {   ui->tabmateriel->setModel(tmpmateriel->afficher());//refresh
           ui->comboBoxid->setModel(tmpmateriel->afficher());
           //ui->tabanimalc->setModel(tmpanim->afficherc());
           ui->comboBox1->setModel(tmpmateriel->afficher());
           QMessageBox::information(nullptr, QObject::tr("Ajouter un materiel"),
                             QObject::tr("materiel ajouté.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);


      // else

           notifier->showMessage("Ok","materiel ajoute",QSystemTrayIcon::Warning,10000);}}

    ui->lineEdit_id->setText("");
    ui->lineEdit_etat->setText("");
    ui->lineEdit_type->setText("");
    ui->dateEdit_achat-> date();
   // ui->lineEdit_maint->setText("");
     ui->comboBox2->currentText();

}

void Thou::on_pushButton_modifier_materiel_clicked()
{
    //QString id = ui->lineEdit_id1->text();
    QString id = ui->comboBoxid->currentText();
    QString type = ui->lineEdit_type1->text();
    QString etat = ui->lineEdit_etat1->text();
    QDate dateachat = ui->lineEdit_achat1->date();
   // QString maint = ui->lineEdit_maint1->text();
    QString maint = ui->comboBox3->currentText();
    QSqlQuery query;
    query.prepare("UPDATE MATERIEL SET ID =:id,TYPE = :type,ETAT = :etat,DATEACHAT=:dateachat, MAINT=:maint where ID = :id");
    query.bindValue(":id",id);
    query.bindValue(":type",type);
    query.bindValue(":etat",etat);
    query.bindValue(":dateachat",dateachat);
    query.bindValue(":maint",maint);
    bool test = query.exec();
    if(test)
    {

        ui->tabmateriel->setModel(tmpmateriel->afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier materiel"),
                    QObject::tr("véhicule Modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer materiel"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->comboBoxid->setModel(tmpmateriel->afficher());
    //ui->lineEdit_id1->clear();
   // ui->lineEdit_type1->clear();
   // ui->lineEdit_etat1->clear();
   // ui->lineEdit_achat1->clear();
   // ui->lineEdit_maint1->clear();


}

void Thou::on_chercher_clicked()
{
    notifier = new QSystemTrayIcon(this);
        notifier->setIcon(QIcon("notification.png"));
        notifier->show();

    int id =ui->lineEdit_chercher->text().toInt();

    if (ui->lineEdit_chercher->text().isEmpty())
     {

         QMessageBox::information(this," erreur "," veuillez verifier le shamp identifiant !") ;

     }
    else{
            QSqlQueryModel *model =tmpmateriel->cherchermateriel(id);
          int idd = model->data(model->index(0,0)).toInt();
           qDebug()<<(idd);
            if(id == idd)
            {
                notifier->showMessage("Ok","materiel Trouvé",QSystemTrayIcon::Warning,10000);

                ui->tabmateriel1->show();
                ui->tabmateriel1->setModel(model);
            }
             else
            {
                QMessageBox::critical(0, qApp->tr("Recherche"),
                    qApp->tr("materiel non trouvé"), QMessageBox::Ok);

}
    }}


void Thou::on_pushButton_supprimer_materiel_clicked()
{
    int id = ui->lineEditsup->text().toInt();
     //int id = ui->comboBox1->currentIndex();
        bool test=tmpmateriel->supprimer(id);
        if(test)
        {   ui->tabmateriel->setModel(tmpmateriel->afficher());
             //ui->comboBox1->setModel(tmpmateriel->afficher());
            //ui->tabanimalc->setModel(tmpanim->afficherc());
            //ui->comboBox_4->setModel(tmpanim->afficher());
            //ui->comboBox1->setModel(tmpmateriel->afficher());
            if (ui->lineEditsup->text().isEmpty())
             {

                 QMessageBox::information(this," erreur "," veuillez verifier le shamp identifiant !") ;

             }
         else

          { QString str = " Vous voulez vraiment supprimer \n le materiel ? ";
                          int ret = QMessageBox::question(this, tr("materiel"),str,QMessageBox::Ok|QMessageBox::Cancel);


                          switch (ret) {
                            case QMessageBox::Ok:
                                if (tmpmateriel->supprimer(id))
                                    QMessageBox ::information(0, qApp->tr("Suppression"),
                                                              qApp->tr("le materiel a été supprimé"), QMessageBox::Ok);


                              break;
                            case QMessageBox::Cancel:

                                break;
                            default:
                                // should never be reached
                                break;
                          }}}
        else
                  {

                      QMessageBox::critical(0, qApp->tr("Suppression"),
                          qApp->tr("materiel inexistant ou en maintenance "), QMessageBox::Cancel);

                  }
       // ui->comboBox1->setModel(tmpmateriel->afficher());
}

void Thou::on_pushButton_ajouter_maintenance_clicked()
{
    int id_mat = ui->lineEdit_id_3->text().toInt();
    //int id_mat = ui->comboboxmaintajout->currentIndex();
    QString type_pan = ui->lineEdit_pan->text();
    QString note = ui->lineEdit_note->text();
    QString agent_maint = ui->lineEdit_agentmaint->text();
    QDate date_prise_en_charge = ui->dateEdit_date->date();
    Maintenance maint (id_mat,type_pan,note,agent_maint,date_prise_en_charge);
    notifier = new QSystemTrayIcon(this);

        notifier->show();

  if (ui->lineEdit_id_3->text().isEmpty())
     // if  (ui->comboboxmaintajout->currentText().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
          else if (ui->lineEdit_pan->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP type de panne !!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }
  else if (ui->lineEdit_note->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP note !!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else if (ui->dateEdit_date->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP date de prise en charge!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
 else if (ui->lineEdit_agentmaint->text().isEmpty())
 // else if (ui->comboBoxagent1->currentText().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP agent de maintenance  !!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else {
      bool test=maint.ajouter();
    if (test)
      //if (query.exec())
    {  ui->tableView->setModel(tmpmaint->afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Ajouter un materiel"),
                          QObject::tr("materiel a maintenir ajouté.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);}


    else

        notifier->showMessage("Ok","materiel a maintenir ajoute",QSystemTrayIcon::Warning,10000);}
      //ui->comboboxmaintajout->setModel(tmpmateriel->afficher2());
      //ui->comboboxmaintajout->setModel(tmpmateriel->afficher());

}

void Thou::on_modifie_maintenance_clicked()
{
    //QString id_mat = ui->lineEdit_id1->text();
   // QString type = ui->lineEdit_type1->text();
    //QString etat = ui->lineEdit_etat1->text();
    //QDate dateachat = ui->lineEdit_achat1->date();
    //QString maint = ui->lineEdit_maint1->text();
   // int id_mat = ui->lineEdit_idmaint->text().toInt();
     QString id_mat = ui->combomodifmaint->currentText();
    QString type_pan = ui->lineEdit_typemaint->text();
    QString note = ui->lineEdit_notemaint->text();
    QString agent_maint = ui->lineEdit_agentmaint_2->text();
    QDate date_prise_en_charge = ui->dateEditdatemaint->date();
    QSqlQuery query;
   query.prepare( "UPDATE MAINTENANCE SET ID_MAT=:id_mat,TYPEPAN=:type_pan,AGENTMAINT=:agent_maint,DPRISEENCHARGE=:date_prise_en_charge,NOTE=:note WHERE ID_MAT=:id_mat");
    query.bindValue(":id_mat",id_mat);
    query.bindValue(":type_pan",type_pan);
    query.bindValue(":note",note);
    query.bindValue(":agent_maint",agent_maint);
    query.bindValue(":date_prise_en_charge",date_prise_en_charge);
    bool test = query.exec();
    if(test)
    {

        ui->tableView->setModel(tmpmaint->afficher());//refresh
        QMessageBox::information(nullptr, QObject::tr("Modifier materiel"),
                    QObject::tr("materiel Modifier.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Supprimer materiel"),
                    QObject::tr("Erreur !.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
     ui->combomodifmaint->setModel(tmpmaint->afficher());
   /* ui->lineEdit_id1->clear();
    ui->lineEdit_type1->clear();
    ui->lineEdit_etat1->clear();
    ui->lineEdit_achat1->clear();
    ui->lineEdit_maint1->clear();*/

}
void Thou::on_pushButton_supprimer_maint_clicked()
{   //int id_mat = ui->combosupprimer->currentIndex();
    int id_mat = ui->lineEdit_sup->text().toInt();

    bool test=tmpmaint->supprimer(id_mat);
    if(test)
    {   ui->tableView->setModel(tmpmaint->afficher());

        if (ui->lineEdit_sup->text().isEmpty())
         {

             QMessageBox::information(this," erreur "," veuillez verifier le shamp identifiant !") ;

         }


        else {
            QString str = " Vous voulez vraiment supprimer \n le produit ayant pour identifiant :"+ ui->lineEdit_id->text();
                      int ret = QMessageBox::question(this, tr("materiel"),str,QMessageBox::Ok|QMessageBox::Cancel);

                      switch (ret) {
                        case QMessageBox::Ok:
                            if (tmpmaint->supprimer(id_mat))
                                QMessageBox ::information(0, qApp->tr("Suppression"),
                                                          qApp->tr("le produit a été supprimé"), QMessageBox::Ok);


                          break;
                        case QMessageBox::Cancel:

                            break;
                        default:
                            // should never be reached
                            break;
                      }}}
    else
              {

                  QMessageBox::critical(0, qApp->tr("Suppression"),
                      qApp->tr("materiel inexistant "), QMessageBox::Cancel);

              }
}

void Thou::on_pushButton_notepad_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Thou::on_actionNEW_triggered()
{
    // Global referencing the current file that we are clearing
        currentFile.clear();

        // Clear the textEdit widget buffer
        ui->textEdit->setText(QString());
}

void Thou::on_actionOPEN_triggered()
{
    // Opens a dialog that allows you to select a file to open
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file");

        // An object for reading and writing files
        QFile file(fileName);

        // Store the currentFile name
        currentFile = fileName;

        // Try to open the file as a read only file if possible or display a
        // warning dialog box
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }

        // Set the title for the window to the file name
        setWindowTitle(fileName);

        // Interface for reading text
        QTextStream in(&file);

        // Copy text in the string
        QString text = in.readAll();

        // Put the text in the textEdit widget
        ui->textEdit->setText(text);

        // Close the file
        file.close();
}

void Thou::on_actionSAVE_AS_triggered()
{
    // Opens a dialog for saving a file
       QString fileName = QFileDialog::getSaveFileName(this, "Save as");

       // An object for reading and writing files
       QFile file(fileName);

       // Try to open a file with write only options
       if (!file.open(QFile::WriteOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
           return;
       }

       // Store the currentFile name
       currentFile = fileName;

       // Set the title for the window to the file name
       setWindowTitle(fileName);

       // Interface for writing text
       QTextStream out(&file);

       // Copy text in the textEdit widget and convert to plain text
       QString text = ui->textEdit->toPlainText();

       // Output to file
       out << text;

       // Close the file
       file.close();
}

void Thou::on_actionPRINT_triggered()
{
    // Allows for interacting with printer
       QPrinter printer;

       // You'll put your printer name here
       printer.setPrinterName("Printer Name");

       // Create the print dialog and pass the name and parent
       QPrintDialog pDialog(&printer, this);

       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Warning", "Cannot Access Printer");
           return;
       }

       // Send the text to the printer
       ui->textEdit->print(&printer);
}

void Thou::on_actionEXIT_triggered()
{
ui->stackedWidget->setCurrentIndex(0);
}

void Thou::on_actionCOPY_triggered()
{
    ui->textEdit->copy();
}

void Thou::on_actionPASTE_triggered()
{
     ui->textEdit->paste();
}

void Thou::on_actionCUT_triggered()
{
    ui->textEdit->cut();
}

void Thou::on_actionUNDO_triggered()
{
    ui->textEdit->undo();
}

void Thou::on_actionREDO_triggered()
{
ui->textEdit->redo();
}

void Thou::on_pushButton_imprimer_clicked()
{
    // Allows for interacting with printer
       QPrinter printer;

       // You'll put your printer name here
       printer.setPrinterName("thouraya epson printer");

       // Create the print dialog and pass the name and parent
       QPrintDialog pDialog(&printer, this);

       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Warning", "Cannot Access Printer");
           return;
       }

       // Send the text to the printer
       ui->textEdit->print(&printer);
}

void Thou::on_pushButton_imprimer_2_clicked()
{
    // Allows for interacting with printer
       QPrinter printer;

       // You'll put your printer name here
       printer.setPrinterName("thouraya epson printer");

       // Create the print dialog and pass the name and parent
       QPrintDialog pDialog(&printer, this);

       if(pDialog.exec() == QDialog::Rejected){
           QMessageBox::warning(this, "Warning", "Cannot Access Printer");
           return;
       }

       // Send the text to the printer
       ui->textEdit->print(&printer);
}

void Thou::on_pushButton_2_clicked()
{
    QString link="https://www.toutpourlaferme.fr/";
        QDesktopServices::openUrl(link);
}



void Thou::on_comboBoxid_currentIndexChanged(int index)
{ Q_UNUSED(index);
    QString id = ui->comboBoxid->currentText();

    QSqlQuery query;
    query.prepare("select * from MATERIEL where ID=id");
    if (query.exec())
    {
     while (query.next())
     {


         ui->lineEdit_type1->setText(query.value(1).toString());
         ui->lineEdit_etat1->setText(query.value(2).toString());
         //ui->lineEdit_achat1->setText(query.value(3).toString());
         QDateTime datee=query.value(3).toDateTime();
         ui->lineEdit_achat1->setDateTime(datee);
         //ui->lineEdit_maint1->setText(query.value(4).toString());


     }
    }
    else {
               QMessageBox::critical(0, qApp->tr("Suppression"),
                   qApp->tr("materiel inexistant "), QMessageBox::Cancel);
           }

}

void Thou::on_comboBox1_currentIndexChanged(int index)
{
    Q_UNUSED(index);
        QString id = ui->comboBoxid->currentText();

        QSqlQuery query;
        query.prepare("select * from MATERIEL where ID='"+id+"'");
        if (query.exec())
        {
         while (query.next())
         {


             ui->lineEditsup->setText(query.value(1).toString());

         }
        }
        else {
                   QMessageBox::critical(0, qApp->tr("Suppression"),
                       qApp->tr("materiel inexistant "), QMessageBox::Cancel);
               }

       // query.exec();
}



/*void Thou::on_pushButton_confirm_clicked()
{
    QString id = ui->comboBoxid->currentText();

    QSqlQuery query;
    query.prepare("select * from MATERIEL where ID='"+id+"'");
    if (query.exec())
    {
     while (query.next())
     {


         ui->lineEditsup->setText(query.value(0).toString());
         ui->lineEdit_type->setText(query.value(1).toString());
         ui->lineEdit_etat->setText(query.value(2).toString());
         QDateTime datee=query.value(4).toDateTime();
         ui->dateEdit_achat->setDateTime(datee);
         ui->lineEdit_maint->setText(query.value(4).toString());

     }
    }
    else {
               QMessageBox::critical(0, qApp->tr("Suppression"),
                   qApp->tr("materiel inexistant "), QMessageBox::Cancel);
           }
}*/



void Thou::on_pushButton_3_clicked()
{
ui->comboBox1->setModel(tmpmateriel->afficher());
}



void Thou::on_pushButton_8_clicked()
{
    ui->comboBoxid->setModel(tmpmateriel->afficher());
}

void Thou::on_pushButton_10_clicked()
{
    ui->tabmateriel->setModel(tmpmateriel->afficher());
}

void Thou::on_pushButton_11_clicked()
{
   ui->tableView->setModel(tmpmaint->afficher());
}

void Thou::on_pushButton_12_clicked()
{
     ui->comboboxmaintajout->setModel(tmpmateriel->afficher2());
     ui->comboBoxagent1->setModel(tmpmaint->afficher1());
     QString id = ui->comboboxmaintajout->currentText();



}



void Thou::on_pushmodifmaint_clicked()
{
  ui->combomodifmaint->setModel(tmpmaint->afficher());
  ui->comboBoxagent->setModel(tmpmaint->afficher1());
}

void Thou::on_combomodifmaint_currentIndexChanged(int index)
{
    Q_UNUSED(index);
        QString id_mat = ui->combomodifmaint->currentText();

        QSqlQuery query;
        query.prepare("select * from MAINTENANCE where ID_MAT=id_mat");
        if (query.exec())
        {
         while (query.next())
         {
             ui->lineEdit_typemaint->setText(query.value(1).toString());
             ui->lineEdit_notemaint->setText(query.value(2).toString());
             ui->lineEdit_agentmaint_2->setText(query.value(4).toString());
          }
        }
        else {
                   QMessageBox::critical(0, qApp->tr("Suppression"),
                       qApp->tr("materiel inexistant "), QMessageBox::Cancel);
               }
}

void Thou::on_pushButton_13_clicked()
{
    ui->combosupprimer->setModel(tmpmaint->afficher());
}


