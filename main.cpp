#include "thouraya.h"
#include "mainwindow.h"

#include "connexion.h"
#include <QApplication>
#include <qsqldatabase.h>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
      MainWindow w;
    Connexion c;

    w.show();

    bool test=c.connecter();
    if(true)
    {
        w.show();


    }
    else
     QMessageBox::critical(nullptr,QObject::tr("data base is not open"),QObject::tr("connection failed.\n","click cancel to exit."),QMessageBox::Cancel);



    return a.exec();

}
