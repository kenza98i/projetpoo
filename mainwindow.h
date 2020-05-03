#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QAction *dossier;
    QAction *suivant;
    QAction *precedent;
    QAction *supprimer;
    QAction *renommer;
    QAction *deplacer;
    QAction *rotaDroite;
    QAction *rotaGauche;
    QAction *quitter;

    QToolBar *toolBarDossier;
    QToolBar *toolBarSuivant;
    QToolBar *toolBarPrecedent;
    QToolBar *toolBarSupprimer;
    QToolBar *toolBarRenommer;
    QToolBar *toolBarDeplacer;
    QToolBar *toolBarRotaDroite;
    QToolBar *toolBarRotaGauche;
    QToolBar *toolbBarQuitter;

    QLabel *image = new QLabel(this);
    QGridLayout *grille = new QGridLayout(this);
    int i;
    int listeimage;
    QString selectDir; // ouvrir un repertoire
    QStringList listimage; // contient le nom de l'image


    QWidget *EcranAffichage;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void ouvrirDossier();
    void afficheImage();
    void suivante();
    void precedente();
    void supprime();
    void renommerImg();
    void deplacerImg();
    void rotationdr();
    void rotationga();
};

#endif // MAINWINDOW_H
