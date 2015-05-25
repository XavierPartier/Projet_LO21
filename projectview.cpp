#include "projectview.h"

projectView::projectView(QWidget *parent){

    //Initialisation de la taille de la fenêtre
    this->setMinimumSize(900,900);

    layout = new QGridLayout;
    layoutHautProjet = new QHBoxLayout;

    ajoutProjets = new QGroupBox("Ajouter des projets");
    ajoutProjets->setMaximumWidth(650);
    listeProjets = new QGroupBox("Liste des projets existants");

    QLineEdit *titreProjet = new QLineEdit("Titre du projet");
    QLineEdit *auteur = new QLineEdit("Auteur du projet");
    QSpinBox *nbTaches = new QSpinBox();
    nbTaches->setMinimum(1);
    nbTaches->setPrefix("Nombre de tâches du projet : ");
    layoutHautProjet->addWidget(titreProjet);
    layoutHautProjet->addWidget(auteur);
    layoutHautProjet->addWidget(nbTaches);

    ajoutProjets->setLayout(layoutHautProjet);

    layout->addWidget(ajoutProjets, 0, 0);
    layout->addWidget(listeProjets, 0, 1);
    this->setLayout(layout);
}
