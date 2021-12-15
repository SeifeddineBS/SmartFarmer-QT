#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "thouraya.h"
#include "login.h"
#include <QMainWindow>
#include "secdialog.h"
Notification N;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

Notification N;

void on_pushButton_Login_clicked();
    void on_pushButton_clicked();

    void on_pushButton_Login_2_clicked();

    void on_pushButton_Login_3_clicked();

private:
    Ui::MainWindow *ui;
    Thou *Th;
   login tmplogin;
      SecDialog *secDialog;
};

#endif // MAINWINDOW_H
