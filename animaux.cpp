#include "ui_animaux.h"
#include "animaux.h"
#include "commandes.h"
#include "livraisons.h"
#include<QMessageBox>
#include <QComboBox>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
#include "notification.h"
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
#include "smtp.h"
#include"QSortFilterProxyModel"


QT_CHARTS_USE_NAMESPACE

Animal::Animal()
{
    id="";
    age=0;
    race="";
    couleur="";
    prix=0;
}
Animal::Animal(QString id,int age,QString race,QString couleur,int prix)
{
    this->id=id;
     this->age=age;
     this->couleur=couleur;
    this->race=race;
    this->prix=prix;

}
int Animal::get_prix(){return prix;}QString Animal::get_race(){return race;}QString Animal::get_couleur(){return couleur;}QString Animal::get_id(){return id;}int Animal::get_age(){return age;}QString Animal::recuperationidcommande(){return ui->tabcommandes->model()->data(ui->tabcommandes->model()->index(ui->tabcommandes->currentIndex().row(),0)).toString();}
Animal::Animal(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Animal)
{
    ui->setupUi(this);
    ui->tabanimal->setModel(tmpanim->afficher());
    ui->tabcommandes->setModel(commande->afficher());
    ui->tabanimalc->setModel(tmpanim->afficherc());
    ui->comboBox_4->setModel(tmpanim->afficher());
    ui->comboBox_9->setModel(tmpanim->afficher2());
    ui->comboBox_idc->setModel(commande->afficher());
    ui->tablivraison->setModel(tmpliv->afficherl());
    ui->comboBox_idl->setModel(tmpliv->afficherlivreur());






    //connect(ui->button_mail, SIGNAL(clicked()),this, SLOT(close()));





}
Animal::~Animal()
{
    delete ui;
}
bool Animal::ajouter()
{   QSqlQuery query;
    query.prepare("INSERT INTO ANIMAUX (ID,AGE,RACE,COULEUR,PRIX)""VALUES(:id,:age,:race,:couleur,:prix)");
    query.bindValue(":id",id);
    query.bindValue(":age",age);
    query.bindValue(":race",race);
    query.bindValue(":couleur",couleur);
    query.bindValue(":prix",prix);

 return query.exec();
}
bool Animal::supprimer()
{
QSqlQuery query;
query.prepare("Delete from ANIMAUX WHERE (ID LIKE '"+id+"')");
return    query.exec();
}
bool Animal::modifier()
{   QSqlQuery query;
    query.prepare( "UPDATE ANIMAUX SET ID=:id, AGE=:age,RACE=:race,COULEUR=:couleur,PRIX=:prix WHERE ID=:id");
    query.bindValue(":id",id);
    query.bindValue(":age",age);
    query.bindValue(":race",race);
    query.bindValue(":couleur",couleur);
    query.bindValue(":prix",prix);


 return query.exec();
}
QSqlQueryModel * Animal::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ANIMAUX");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("AGE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("COULEUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel * Animal::afficher2()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from CLIENT");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("TEL "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("NOM"));

    return model;
}
QSqlQueryModel * Animal::afficherc()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from ANIMAUX");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("AGE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("COULEUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));
    return model;
}
void Animal::on_pushButton_ajouter_clicked()
{

    QString id = ui->lineEdit_id->text();
    int age = ui->lineEdit_age->text().toInt();
    QString race = ui->lineEdit_race->text();
    QString couleur = ui->lineEdit_couleur->text();
    int prix = ui->lineEdit_prix->text().toInt();


  Animal anim (id,age,race,couleur,prix);


  if (ui->lineEdit_id->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
          else if (ui->lineEdit_age->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Age!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }
  else if (ui->lineEdit_race->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP Race !!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else if (ui->lineEdit_couleur->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Couleur  !!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
  else if (ui->lineEdit_prix->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER Prix  !!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }


  else {
      bool test=anim.ajouter();
    if (test)
    {   ui->tabanimal->setModel(tmpanim->afficher());//refresh
        //ui->comboBox_8->setModel(tmpanim->afficher());
        ui->tabanimalc->setModel(tmpanim->afficherc());
        ui->comboBox_4->setModel(tmpanim->afficher());
        //ui->comboBox_5->setModel(tmpanim->afficher());

       N.notification_ajoutanimal();}


    }

 ui->lineEdit_id->setText("");
 ui->lineEdit_age->setText("");
 ui->lineEdit_race->setText("");
 ui->lineEdit_couleur->setText("");
 ui->lineEdit_prix->setText("");

}
void Animal::on_pushButton_supprimer_clicked()
{

    if(ui->tabanimal->currentIndex().row()==-1)
        QMessageBox::information(nullptr, QObject::tr("Suppression"),
                          QObject::tr("Veuillez Choisir un Animal du Tableau.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
    else
    {
        Animal anim(ui->tabanimal->model()->data(ui->tabanimal->model()->index(ui->tabanimal->currentIndex().row(),0)).toString(),ui->tabanimal->model()->data(ui->tabanimal->model()->index(ui->tabanimal->currentIndex().row(),1)).toInt(),ui->tabanimal->model()->data(ui->tabanimal->model()->index(ui->tabanimal->currentIndex().row(),2)).toString(),ui->tabanimal->model()->data(ui->tabanimal->model()->index(ui->tabanimal->currentIndex().row(),3)).toString(),ui->tabanimal->model()->data(ui->tabanimal->model()->index(ui->tabanimal->currentIndex().row(),2)).toInt());



            //ui->lineEdit_id_6->setText("");
            //ui->REF->setModel(tmp.getIDs());
            QString str = " Vous voulez vraiment supprimer \n l'animal :";
                              int ret = QMessageBox::question(this, tr("Animal"),str,QMessageBox::Ok|QMessageBox::Cancel);

                              switch (ret) {
                                case QMessageBox::Ok:
                                    if (anim.supprimer()){
                                       N.notification_supprimeranimal();
                                    ui->tabanimal->setModel(tmpanim->afficher());
                                    ui->comboBox_4->setModel(tmpanim->afficher());
                                    ui->tabanimalc->setModel(tmpanim->afficherc());

                                    //ui->comboBox_8->setModel(tmpanim->afficher());
                                    }
                                    else
                                      {

                                          QMessageBox::critical(0, qApp->tr("Suppression"),
                                              qApp->tr("Animal non trouvé "), QMessageBox::Cancel);
      }



                                  break;
                                case QMessageBox::Cancel:

                                    break;
                                default:
                                    // should never be reached
                                    break;
                              }


}}
void Animal::on_pushButton_modifier_clicked()
{

        QString id=ui->lineEdit_id1->text();
        int age = ui->lineEdit_age1->text().toInt();
        QString race = ui->lineEdit_race1->text();
        QString couleur = ui->lineEdit_couleur1->text();
        int prix = ui->lineEdit_prix1->text().toInt();
        Animal anim (id,age,race,couleur,prix);

        QSqlQuery query;

        bool test=anim.modifier();
        if(test)
        {

            ui->tabanimal->setModel(tmpanim->afficher());//refresh
            //ui->comboBox_8->setModel(tmpanim->afficher());
            ui->tabanimalc->setModel(tmpanim->afficherc());
            ui->comboBox_4->setModel(tmpanim->afficher());
            //ui->comboBox_5->setModel(tmpanim->afficher());

            N.notification_modifieranimal();


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Supprimer animal"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        //ui->comboBox_8->setModel(tmpanim->afficher());
        ui->lineEdit_age1->clear();
        ui->lineEdit_race1->clear();
        ui->lineEdit_couleur1->clear();
        ui->lineEdit_prix1->clear();
        ui->lineEdit_id1->clear();




}
void Animal::on_pushButton_ajouterc_clicked()
{    QString id = ui->lineEdit_idc->text();

    QString idc=ui->comboBox_9->currentText();


    QDate dat =ui->lineEdit_datec->date();
    QString idd=ui->comboBox_4->currentText();
       QSqlQuery query;
       query.prepare("SELECT * FROM ANIMAUX WHERE (ID LIKE '"+idd+"')");

       if (query.exec())
       {
        while (query.next())
        {
            commande->supprimeranimal(idd);

            ui->lineEdit_prixc->setText(query.value(4).toString());
            prix= ui->lineEdit_prixc->text().toInt();





        }
       }




  Commande cm (id,dat,idc,prix);


  if (ui->lineEdit_idc->text().isEmpty())
   {

       QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
       QMessageBox::critical(0, qApp->tr("Ajout"),

                       qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

   }
          else if (ui->lineEdit_datec->text().isEmpty())
           {

               QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP DATE!!!!") ;
               QMessageBox::critical(0, qApp->tr("Ajout"),

                               qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

           }





  else {
      bool test=cm.ajouter();
    if (test)
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM ANIMAUX WHERE (ID LIKE '"+idd+"')");

        if (query.exec())
        {
         while (query.next())
         {
             commande->supprimeranimal(idd);

             ui->lineEdit_prixc->setText(query.value(4).toString());
             prix= ui->lineEdit_prixc->text().toInt();





         }}
         QSqlQuery query1;
         query1.prepare("SELECT * FROM CLIENT WHERE (CIN LIKE '"+idc+"')");
         if (query1.exec())
         {
          while (query1.next())
          {            QString email=query1.value(5).toString();


              Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
              connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


             smtp->sendMail("farmeresprit414@gmail.com",email,"Salut "+query1.value(2).toString(),"Commande confirmée");}}







        ui->tabanimal->setModel(tmpanim->afficher());
        ui->tabcommandes->setModel(commande->afficher());
        //ui->comboBox_8->setModel(tmpanim->afficher());
        ui->tabanimalc->setModel(tmpanim->afficherc());
        ui->comboBox_4->setModel(tmpanim->afficher());
        ui->comboBox_idc->setModel(commande->afficher());


        N.notification_ajoutcommande();

    }



    }

  ui->lineEdit_datec->clear();

}
void Animal::on_pushButton_modifierc_clicked()
{

        QString id=ui->lineEdit_idc1->text();


        QString idc=ui->comboBox_10->currentText();
        QDate dat = ui->lineEdit_datec1->date();
        int prix = ui->lineEdit_prixc1->text().toInt();
        Commande cm (id,dat,idc,prix);

        QSqlQuery query;

        bool test=cm.modifier();
        if(test)
        {

            ui->tabcommandes->setModel(cm.afficher());//refresh
            ui->tabcommandes->setModel(commande->afficher());


            N.notification_modifiercommande();

            ui->lineEdit_datec1->clear();
            ui->lineEdit_prixc1->clear();
            ui->lineEdit_idc1->clear();


        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Modifier Commande"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }





    }
void Animal::on_pushButton_supprimerc_clicked()
{
    if(ui->tabcommandes->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Veuillez Choisir une Commande du Tableau.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        else
        {
            Commande com(ui->tabcommandes->model()->data(ui->tabcommandes->model()->index(ui->tabcommandes->currentIndex().row(),0)).toString(),ui->tabcommandes->model()->data(ui->tabcommandes->model()->index(ui->tabcommandes->currentIndex().row(),1)).toDate(),ui->tabcommandes->model()->data(ui->tabcommandes->model()->index(ui->tabcommandes->currentIndex().row(),2)).toString(),ui->tabcommandes->model()->data(ui->tabcommandes->model()->index(ui->tabcommandes->currentIndex().row(),3)).toInt());

                QString str = " Vous voulez vraiment supprimer \n la Commande :";
                                  int ret = QMessageBox::question(this, tr("Commande"),str,QMessageBox::Ok|QMessageBox::Cancel);

                                  switch (ret) {
                                    case QMessageBox::Ok:
                                        if (com.supprimer()){
                                           N.notification_supprimercommande();
                                       ui->tabcommandes->setModel(commande->afficher());
                                       ui->comboBox_idc->setModel(commande->afficher());

                                        }
                                        else
                                          {

                                              QMessageBox::critical(0, qApp->tr("Suppression"),
                                                  qApp->tr("Commande non trouvée "), QMessageBox::Cancel);
          }



                                      break;
                                    case QMessageBox::Cancel:

                                        break;
                                    default:
                                        // should never be reached
                                        break;
                                  }


    }
}
QSqlQueryModel * Animal::trianimauxas()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM ANIMAUX ORDER BY AGE ASC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("AGE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("COULEUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
QSqlQueryModel * Animal::trianimauxds()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * FROM ANIMAUX ORDER BY AGE DESC");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("AGE "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("COULEUR"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
void Animal::on_pushButton_trianimauxas_clicked(){
    ui->tabanimal->setModel(tmpanim->trianimauxas());

}
void Animal::on_pushButton_trianimauxds_clicked(){
    ui->tabanimal->setModel(tmpanim->trianimauxds());

}
void Animal::on_pushButton_tricommandeas_clicked(){

    ui->tabcommandes->setModel(commande->tricommandeas());

}
void Animal::on_pushButton_tricommandeds_clicked(){

    ui->tabcommandes->setModel(commande->tricommandeds());

}
void Animal::on_pushButton_resetanim_clicked(){
 ui->tabanimal->setModel(tmpanim->afficher());

}
void Animal::on_pushButton_resetcommande_clicked(){
 ui->tabcommandes->setModel(commande->afficher());

}
void Animal::on_pushButton_pdfc_clicked(){
    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
           QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfCommandes.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(2300,1200,"Liste Des Commandes");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(1500,200,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(300,3300,"ID");
               painter.drawText(2300,3300,"Date");
               painter.drawText(4300,3300,"IDC");
               painter.drawText(6300,3300,"PRIX");

               QSqlQuery query;
               query.prepare("select * from COMMANDES");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300,i,query.value(0).toString());
                   painter.drawText(2300,i,query.value(1).toString());
                   painter.drawText(4300,i,query.value(2).toString());
                   painter.drawText(6300,i,query.value(3).toString());

                  i = i +500;
               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                   if (reponse == QMessageBox::Yes)
                   {
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfCommandes.pdf"));

                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }
}
void Animal::on_pushButton_pdf_clicked(){
    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
           QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfAnimaux.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(2300,1200,"Liste Des Animaux");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(1500,200,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(300,3300,"ID");
               painter.drawText(2300,3300,"AGE");
               painter.drawText(4300,3300,"RACE");
               painter.drawText(6300,3300,"COULEUR");
               painter.drawText(8300,3300,"PRIX");

               QSqlQuery query;
               query.prepare("select * from ANIMAUX");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300,i,query.value(0).toString());
                   painter.drawText(2300,i,query.value(1).toString());
                   painter.drawText(4300,i,query.value(2).toString());
                   painter.drawText(6300,i,query.value(3).toString());
                   painter.drawText(8300,i,query.value(4).toString());

                  i = i +500;
               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                   if (reponse == QMessageBox::Yes)
                   {
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfAnimaux.pdf"));

                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }
}
QSqlQueryModel *Animal::displayClause(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT * FROM ANIMAUX " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("AGE"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("RACE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("COULEUR"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("PRIX"));

    return model;
}
void Animal::on_lineEdit_rechercheanimal_textChanged()
{
    //Animal *tmpanim;

    if(ui->lineEdit_rechercheanimal->text()!="")
{        QString b=ui->comboBox_recherche->currentText();
        QString a=ui->lineEdit_rechercheanimal->text();
        ui->tabanimal->setModel(tmpanim->displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
    }
     else
     ui->tabanimal->setModel(tmpanim->afficher());
}
void Animal::on_lineEdit_recherchecommande_textChanged()
{

    if(ui->lineEdit_recherchecommande->text()!="")
{        QString b=ui->comboBox_recherchecommande->currentText();
        QString a=ui->lineEdit_recherchecommande->text();
        ui->tabcommandes->setModel(commande->displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
    }
     else
     ui->tabcommandes->setModel(commande->afficher());
}
void Animal::on_tabanimal_activated(const QModelIndex &index)
{
    QString id=ui->tabanimal->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM ANIMAUX WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                ui->lineEdit_id1->setText(query.value(0).toString());
                ui->lineEdit_age1->setText(query.value(1).toString());
                ui->lineEdit_race1->setText(query.value(2).toString());
                ui->lineEdit_couleur1->setText(query.value(3).toString());
                ui->lineEdit_prix1->setText(query.value(4).toString());

            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }
}
void Animal::on_tabcommandes_activated(const QModelIndex &index)
{
    QString id=ui->tabcommandes->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM COMMANDES WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {       ui->comboBox_10->setModel(tmpanim->afficher2());

                QDateTime datee=query.value(1).toDateTime();
                ui->lineEdit_datec1->setDateTime(datee);
                ui->lineEdit_prixc1->setText(query.value(3).toString());
                ui->lineEdit_idc1->setText(id);


            }

        }
        else
        {
            QObject::tr("ERREUR");
        }
}

void Animal::on_pushButton_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from COMMANDES where PRIX < 500 ");
            float salaire=model->rowCount();
            model->setQuery("select * from COMMANDES where PRIX  between 500 and 1000 ");
            float salairee=model->rowCount();
            model->setQuery("select * from COMMANDES where PRIX>1000 ");
            float salaireee=model->rowCount();
            float total=salaire+salairee+salaireee;
            QString a=QString("moins de 500 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
            QString b=QString("entre 500 et 1000 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
            QString c=QString("+1000 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
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
            chart->setTitle("Pourcentage Par Prix :Nombre Des Commandes "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();


}
void Animal::mailSent(QString status)
{
    if(status == "Message sent")
        N.mail_commande();
}






void Animal::on_lineEdit_recherchelivraison_textChanged()
{
    //Animal *tmpanim;

    if(ui->lineEdit_recherchelivraison->text()!="")
{        QString b=ui->comboBox_recherchelivraison->currentText();
        QString a=ui->lineEdit_recherchelivraison->text();
        ui->tablivraison->setModel(tmpliv->displayClause("WHERE ("+b+" LIKE '%"+a+"%')"));
    }
     else
     ui->tablivraison->setModel(tmpliv->afficherl());
}
void Animal::on_tablivraison_activated(const QModelIndex &index)
{
    QString id=ui->tablivraison->model()->data(index).toString();
        QSqlQuery query;
        query.prepare("SELECT * FROM LIVRAISONS WHERE ID='"+id+"'");
        if(query.exec())
        {
            while(query.next())
            {
                QDateTime datee=query.value(3).toDateTime();
                ui->lineEdit_datel1->setDateTime(datee);
                ui->lineEdit_idl1->setText(query.value(0).toString());
                ui->comboBox_idc1->setModel(commande->afficher());
                ui->comboBox_idl1->setModel(tmpliv->afficherlivreur());

                ui->lineEdit_prixl1->setText(query.value(4).toString());
                ui->lineEdit_lieul1->setText(query.value(5).toString());



            }

        }
        else
        {
            QObject::tr("Veuillez Choisir Un ID Du Tableau SVP");
        }
}






void Animal::on_pushButton_pdfl_clicked()
{
    //QDateTime datecreation = date.currentDateTime();
    //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
           QPdfWriter pdf("C:/Users/ASUS/Downloads/PdfLivraisons.pdf");
           QPainter painter(&pdf);
          int i = 4000;
               painter.setPen(Qt::blue);
               painter.setFont(QFont("Arial", 30));
               painter.drawText(2300,1200,"Liste Des Livraisons");
               painter.setPen(Qt::black);
               painter.setFont(QFont("Arial", 50));
              // painter.drawText(1100,2000,afficheDC);
               painter.drawRect(1500,200,7300,2600);
               //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));
               painter.drawRect(0,3000,9600,500);
               painter.setFont(QFont("Arial", 9));
               painter.drawText(300,3300,"ID");
               painter.drawText(1800,3300,"IDC");
               painter.drawText(3300,3300,"IDL");
               painter.drawText(4800,3300,"DATE");
               painter.drawText(6300,3300,"PRIX");
               painter.drawText(7800,3300,"Lieu");


               QSqlQuery query;
               query.prepare("select * from LIVRAISONS");
               query.exec();
               while (query.next())
               {
                   painter.drawText(300,i,query.value(0).toString());
                   painter.drawText(1800,i,query.value(1).toString());
                   painter.drawText(3300,i,query.value(2).toString());
                   painter.drawText(4800,i,query.value(3).toString());
                   painter.drawText(6300,i,query.value(4).toString());
                   painter.drawText(7800,i,query.value(5).toString());


                  i = i +500;
               }
               int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
                   if (reponse == QMessageBox::Yes)
                   {
                       QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/ASUS/Downloads/PdfLivraisons.pdf"));

                       painter.end();
                   }
                   if (reponse == QMessageBox::No)
                   {
                        painter.end();
                   }
}

void Animal::on_pushButton_trilivraisonas_clicked()
{
    ui->tablivraison->setModel(tmpliv->trilivraisonas());

}



void Animal::on_pushButton_trilivraisonds_clicked()
{
    ui->tablivraison->setModel(tmpliv->trilivraisonds());

}

void Animal::on_pushButton_resetlivraison_clicked()
{
    ui->tablivraison->setModel(tmpliv->afficherl());

}



void Animal::on_pushButton_supprimerl_clicked()
{
    if(ui->tablivraison->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Veuillez Choisir une livraison du Tableau.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        else
        {
        Livraison liv(ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),0)).toString(),ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),1)).toString(),ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),2)).toString(),ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),3)).toDate(),ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),4)).toInt(),ui->tablivraison->model()->data(ui->tablivraison->model()->index(ui->tablivraison->currentIndex().row(),5)).toString());

                QString str = " Vous voulez vraiment supprimer \n la Commande :";
                                  int ret = QMessageBox::question(this, tr("Commande"),str,QMessageBox::Ok|QMessageBox::Cancel);

                                  switch (ret) {
                                    case QMessageBox::Ok:
                                        if (liv.supprimerl()){
                                           N.notification_supprimerlivraison();
                                       ui->tablivraison->setModel(tmpliv->afficherl());
                                        }
                                        else
                                          {

                                              QMessageBox::critical(0, qApp->tr("Suppression"),
                                                  qApp->tr("Commande non trouvée "), QMessageBox::Cancel);
          }



                                      break;
                                    case QMessageBox::Cancel:

                                        break;
                                    default:
                                        // should never be reached
                                        break;
                                  }


    }
}

void Animal::on_pushButton_modifierl_clicked()
{
    QString id = ui->lineEdit_idl1->text();
        QString idc=ui->comboBox_idc1->currentText();
         QString idl=ui->comboBox_idl1->currentText();
        QDate dat =ui->lineEdit_datel1->date();
        int prix = ui->lineEdit_prixl1->text().toInt();
        QString lieu =ui->lineEdit_lieul1->text();

        Livraison liv (id,idc,idl,dat,prix,lieu);

        QSqlQuery query;

        bool test=liv.modifierl();
        if(test)
        {

            ui->tablivraison->setModel(tmpliv->afficherl());


            N.notification_modifierlivraison();

            ui->lineEdit_datel1->clear();



        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Modifier Commande"),
                        QObject::tr("Erreur !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }




}

void Animal::on_pushButton_ajouterl_clicked()
{
    QString id = ui->lineEdit_idl->text();
    int prix=0;
       QString idc=ui->comboBox_idc->currentText();
       QString idl=ui->comboBox_idl->currentText();
       QDate dat =ui->lineEdit_datel->date();
       QString client;
       QString lieu;

          QSqlQuery query;
          query.prepare("SELECT * FROM COMMANDES WHERE (ID LIKE '"+idc+"')");

          if (query.exec())
          {
           while (query.next())
           {

               ui->lineEdit_prixl->setText(query.value(3).toString());
               client=query.value(2).toString();
               QSqlQuery query1;
               query1.prepare("SELECT LIEU FROM CLIENT WHERE (CIN LIKE '"+client+"')");

               if (query1.exec())
               {
                while (query1.next())
                {
                       lieu=query1.value(0).toString();

                }}

                prix= (ui->lineEdit_prixl->text().toInt())*1.2;
               commande->supprimercommandel(idc);






           }
          }




     Livraison liv (id,idc,idl,dat,prix,lieu);


     if (ui->lineEdit_idl->text().isEmpty())
      {

          QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP IDENTIFIANT!!!!") ;
          QMessageBox::critical(0, qApp->tr("Ajout"),

                          qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

      }
             else if (ui->lineEdit_datel->text().isEmpty())
              {

                  QMessageBox::information(this," ERREUR "," VEUILLEZ VERIFIER CHAMP DATE!!!!") ;
                  QMessageBox::critical(0, qApp->tr("Ajout"),

                                  qApp->tr("Probleme d'ajout"), QMessageBox::Cancel);

              }





     else {
         bool test=liv.ajouterl();
       if (test)
       {


           QSqlQuery query;
           query.prepare("SELECT * FROM LIVREUR WHERE (ID LIKE '"+idl+"')");
           if (query.exec())
           {
            while (query.next())
            {            QString email=query.value(5).toString();


                Smtp* smtp = new Smtp("farmeresprit414@gmail.com","farmer1919","smtp.gmail.com",465);
                connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


               smtp->sendMail("farmeresprit414@gmail.com",email,"Salut "+query.value(1).toString(),"Votre Prochaine livraison est le"+dat.toString("yyyy-MM-dd")+"à"+lieu);









            }
           }

           ui->tabcommandes->setModel(commande->afficher());
           ui->tablivraison->setModel(tmpliv->afficherl());
           ui->comboBox_idc->setModel(commande->afficher());




           N.notification_ajoutlivraison();

       }



       }

     ui->lineEdit_datel->clear();

}

void Animal::on_stat_button_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from LIVRAISONS where PRIX < 500 ");
            float salaire=model->rowCount();
            model->setQuery("select * from LIVRAISONS where PRIX  between 500 and 1000 ");
            float salairee=model->rowCount();
            model->setQuery("select * from LIVRAISONS where PRIX>1000 ");
            float salaireee=model->rowCount();
            float total=salaire+salairee+salaireee;
            QString a=QString("moins de 500 Dinars "+QString::number((salaire*100)/total,'f',2)+"%" );
            QString b=QString("entre 500 et 1000 Dinars "+QString::number((salairee*100)/total,'f',2)+"%" );
            QString c=QString("+1000 Dinars "+QString::number((salaireee*100)/total,'f',2)+"%" );
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
            chart->setTitle("Pourcentage Par Prix :Nombre Des LIVRAISONS "+ QString::number(total));
            chart->legend()->hide();
            // Used to display the chart
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}
