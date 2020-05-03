#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dossier = new QAction("&dossier",this);
    suivant = new QAction("&suivant",this);
    precedent = new QAction("&precedent",this);
    supprimer= new QAction("&supprimer",this);
    renommer = new QAction("&renommer",this);
    deplacer = new QAction("&deplacer",this);
    rotaDroite = new QAction("&rotation droite",this);
    rotaGauche = new QAction("&rotation gauche",this);
    quitter = new QAction("&quitter",this);

    toolBarDossier=addToolBar("dossier");
    toolBarPrecedent=addToolBar("precedent");
    toolBarSuivant=addToolBar("suivant");
    toolBarSupprimer=addToolBar("supprimer");
    toolBarRenommer=addToolBar("renommer");
    toolBarDeplacer=addToolBar("deplacer");
    toolBarRotaDroite=addToolBar("rotation droite");
    toolBarRotaGauche=addToolBar("rotation gauche");
    toolbBarQuitter=addToolBar("quitter");

    toolBarDossier->addAction(dossier);
    toolBarPrecedent->addAction(precedent);
    toolBarSuivant->addAction(suivant);
    toolBarSupprimer->addAction(supprimer);
    toolBarRenommer->addAction(renommer);
    toolBarDeplacer->addAction(deplacer);
    toolBarRotaDroite->addAction(rotaDroite);
    toolBarRotaGauche->addAction(rotaGauche);
    toolbBarQuitter->addAction(quitter);

    connect(quitter,SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(dossier,SIGNAL(triggered()),this,SLOT(ouvrirDossier()));
    connect(suivant,SIGNAL(triggered()),this,SLOT(suivante()));
    connect(precedent,SIGNAL(triggered()),this,SLOT(precedente()));
    connect(supprimer,SIGNAL(triggered()),this,SLOT(supprime()));
    connect(renommer,SIGNAL(triggered()),this,SLOT(renommerImg()));
    connect(deplacer,SIGNAL(triggered()),this,SLOT(deplacerImg()));
    connect(rotaDroite,SIGNAL(triggered()),this,SLOT(rotationdr()));
    connect(rotaGauche,SIGNAL(triggered()),this,SLOT(rotationga()));

    resize(QGuiApplication::primaryScreen()->availableSize()*2/4);
    EcranAffichage = new QWidget;
    setCentralWidget(EcranAffichage);
    EcranAffichage->setFixedSize(1200,600);
    grille->addWidget(image,0,0);
    EcranAffichage->setLayout(grille);

}

MainWindow::~MainWindow()
{

}

void MainWindow ::ouvrirDossier()
{
    listeimage=0;
    i=0;

    selectDir = QFileDialog::getExistingDirectory
    (
        this,
        tr("Ouvrir un répertoire"),
        "",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    if(selectDir!="") afficheImage();

}

void MainWindow::afficheImage()
{

    QStringList listFilter;
    listFilter << "*.jpg";
    listFilter << "*.png";
    listFilter << "*.gif";
    listFilter << "*.jpeg";

    // On déclare un QDirIterator dans lequel on indique que l'on souhaite parcourir un répertoire et ses sous-répertoires.
    // De plus, on spécifie le filtre qui nous permettra de récupérer uniquement les fichiers du type souhaité.
    QDirIterator dirIterator(selectDir, listFilter ,QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);

    // Variable qui contiendra tous les fichiers correspondant à notre recherche

    // Tant qu'on n'est pas arrivé à la fin de l'arborescence...
    while(dirIterator.hasNext())
    {
        // ...on va au prochain fichier correspondant à notre filtre
        listimage << dirIterator.next();
        listeimage++;
    }

    image->setPixmap(QPixmap(listimage[i]));

}
void MainWindow::supprime()
{
    QFile file(listimage[i]);
    if(file.exists())
    {
        int suppr=QMessageBox::question(this,"suppression","voulez-vous supprimer ?",QMessageBox::Yes | QMessageBox::No);
        if(suppr==QMessageBox::Yes)
        {
            file.remove();
            listimage[i]=listimage[i+1];
            if(listeimage!=0) afficheImage();
        }
    }
}

void MainWindow::suivante()
{
    if(i!=listeimage)
    {
        image->setPixmap(QPixmap(listimage[i]));
        i++;
    }
    afficheImage();
}
void MainWindow::precedente()
{
    if(i!=0)
    {
        image->setPixmap(QPixmap(listimage[i]));
        i--;
    }
    afficheImage();
}
void MainWindow::renommerImg()
{
    if(listimage[i]!="")
    {
        QString a= QFileInfo(listimage[i]).absolutePath(); // recupere le chemin d'acces à l'image
        QString b= QFileInfo(listimage[i]).suffix(); // recupere l'extension de l'image
        QString nom ="";
        nom = QInputDialog::getText(this,"","nouveau nom");
        if(nom!="")
        {
            QMessageBox::information(this,"renommer fichier" ,"Fichier renommer:"+nom+"."+b);
            nom=a+"/"+nom+"."+b;
            QFile::rename(listimage[i],nom);// renomme le fichier
        }
    }
}
void MainWindow::deplacerImg()
{
    if(listimage[i]!="")
    {
        QFile f(listimage[i]);
        QString str = f.fileName();
        QStringList parts = str.split("/");
        QString nom = parts.at(parts.size()-1);

        QString nouveauN="";
        nouveauN= QFileDialog::getExistingDirectory(this,tr("repertoire"),"",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        nom=nouveauN+"/"+nom;
        if(nouveauN==""){}
        else
        {
            if(listimage[i]==nom) QMessageBox::information(this,"Erreur","choisissez un autre dossier ");
            else
            {
                QMessageBox::information(this,"déplacer","le fichier à été deplacé dans:" +listimage[i]);
                QFile::rename(listimage[i],nom);
                listimage[i]=nom;
            }
        }
    }
}

void MainWindow::rotationdr()
{
//    int largeur = image->pixmap()->width();
//    int hauteur = image->pixmap()->height();
    QPixmap pixmap(*image->pixmap());
    QMatrix rotation;
    rotation.rotate(90);
    pixmap =pixmap.transformed(rotation);
    pixmap.scaled(801,701);
    image->setPixmap(pixmap);

}
void MainWindow::rotationga()
{
    QPixmap pixmap(*image->pixmap());
    QMatrix rotation;
    rotation.rotate(-90);
    pixmap =pixmap.transformed(rotation);
    pixmap.scaled(801,701);
    image->setPixmap(pixmap);

}
