#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "thouraya.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <QPdfWriter>
#include <QDesktopServices>
#include <QUrl>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
ui->setupUi(this);


//ui->tabetudiant->setModel(tmpfournisseur.afficher());
//  ui->comboBox_id->setModel(tmpfournisseur.afficher());
  //  ui->comboBox_1->setModel(tmpfournisseur.afficher());
  //  ui->comboBox_3->setModel(tmplogin.afficher());
  //  ui->comboBox_2->setModel(tmplogin.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}

//






void MainWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
     QString password = ui->lineEdit_password->text();
     QSqlQuery query ;

        query.prepare("SELECT * FROM LOGIN WHERE USERNAME=\'"+username+"\' AND PASSWORD=\'"+ui->lineEdit_password->text()+"\' ");
int test=0;
        if(query.exec()){
            while(query.next())
                        { if (test==1){   QMessageBox::information(nullptr, QObject::tr("MDP"),
                             QObject::tr("Mot De Passe correcte"), QMessageBox::Cancel);


                }
                Th = new Thou(this);
                         Th->show();
                test=1;


        }}

        if(test!=1){
            QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                          QObject::tr("Veuillez saisir de nouveau.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);
        }


}




void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);


}

void MainWindow::on_pushButton_Login_2_clicked()
{

    QString username = ui->lineEdit_username_2->text();
    QString password = ui->lineEdit_password_2->text();
    QSqlQuery query ;
    int test=0;

       query.prepare("SELECT * FROM LOGIN WHERE USERNAME=\'"+username+"\' AND PASSWORD=\'"+password+"\' ");

       if(query.exec()){
           while(query.next())
                       {
               test=1;
               QString password_new = ui->lineEdit_password_3->text();
               QSqlQuery query1 ;

               query1.prepare( "UPDATE LOGIN SET PASSWORD=\'"+password_new+"\'WHERE USERNAME=\'"+username+"\'");
                query1.exec();
                    QMessageBox::information(nullptr, QObject::tr("MDP"),
                              QObject::tr("Mot De Passe modifié"), QMessageBox::Cancel);






       }}
       if(test!=1){
           QMessageBox::information(nullptr, QObject::tr("Erreur"),
                                         QObject::tr("Veuillez saisir de nouveau.\n"
                                                     "Click Cancel to exit."), QMessageBox::Cancel);
       }

}

void MainWindow::on_pushButton_Login_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);

}
