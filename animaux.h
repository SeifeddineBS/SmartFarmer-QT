#ifndef ANIMAL_H
#define ANIMAL_H
#include <QDialog>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include "commandes.h"
#include "notification.h"
#include "livraisons.h"

namespace Ui {
class Animal;
}
class Animal : public QDialog
{
    Q_OBJECT
    QString id,race,couleur;
    int age,prix;
public:
    explicit Animal(QWidget *parent = nullptr);
    Animal();
    Animal (QString,int,QString,QString,int);
    QString get_id();
    int get_age();
    int get_prix();
    QString recuperationidcommande();
    QString get_race();
    QString get_couleur();
    bool ajouter();
    bool modifier();
    QSqlQueryModel *afficher();
    QSqlQueryModel *afficher2();
    QSqlQueryModel *afficherc();
    QSqlQueryModel *trianimauxas();
    QSqlQueryModel *trianimauxds();

    bool supprimer();
    ~Animal();
private slots:
void on_pushButton_ajouter_clicked();
void on_pushButton_supprimer_clicked();
void on_pushButton_modifier_clicked();
void on_pushButton_pdf_clicked();
void on_pushButton_pdfc_clicked();
void on_pushButton_supprimerc_clicked();
void on_pushButton_ajouterc_clicked();
void on_pushButton_modifierc_clicked();
void on_pushButton_trianimauxas_clicked();
void on_pushButton_trianimauxds_clicked();
void on_pushButton_tricommandeas_clicked();
void on_pushButton_tricommandeds_clicked();
void on_pushButton_resetanim_clicked();
void on_pushButton_resetcommande_clicked();
void on_lineEdit_rechercheanimal_textChanged();
void on_lineEdit_recherchecommande_textChanged();
void on_lineEdit_recherchelivraison_textChanged();

void on_tabanimal_activated(const QModelIndex &index);
void on_tabcommandes_activated(const QModelIndex &index);
void on_tablivraison_activated(const QModelIndex &index);

QSqlQueryModel *displayClause(QString cls);
void on_pushButton_clicked();

void mailSent(QString);





void on_pushButton_pdfl_clicked();

void on_pushButton_trilivraisonas_clicked();


void on_pushButton_trilivraisonds_clicked();

void on_pushButton_resetlivraison_clicked();


void on_pushButton_supprimerl_clicked();

void on_pushButton_modifierl_clicked();

void on_pushButton_ajouterl_clicked();

void on_stat_button_clicked();

private:
    Ui::Animal *ui;
    Animal *tmpanim;
    Commande   *commande;
    Notification N;
    Livraison *tmpliv;
};

#endif // ANIMAL_H
