#include "calendarview.h"

calendarView::calendarView(){

    //Initialisation de la taille de la fenêtre
    this->setMinimumSize(900,900);

    initialise();

    QObject::connect(suivant, SIGNAL(clicked()), this, SLOT(incremente()));
    QObject::connect(precedent, SIGNAL(clicked()), this, SLOT(decremente()));
}

void calendarView::initialise(){
    int sizeOfWidget = 150;

    //Récupération de la date courante et initialisation du calendrier
    dateCourante = new QDate();
    jour1 = new QDate();
    jour2 = new QDate();
    jour3 = new QDate();
    jour4 = new QDate();
    jour5 = new QDate();
    jour6 = new QDate();
    jour7 = new QDate();
    *dateCourante = QDate::currentDate();
    *jour1 = dateCourante->addDays(-3);
    jour1String = jour1->toString("dddd");
    jour1StringChiffre = jour1->toString("dd");
    *jour2 = dateCourante->addDays(-2);
    jour2String = jour2->toString("dddd");
    jour2StringChiffre = jour2->toString("dd");
    *jour3 = dateCourante->addDays(-1);
    jour3String = jour3->toString("dddd");
    jour3StringChiffre = jour3->toString("dd");
    *jour4 = *dateCourante;
    jour4String = jour4->toString("dddd");
    jour4StringChiffre = jour4->toString("dd");
    *jour5 = dateCourante->addDays(1);
    jour5String = jour5->toString("dddd");
    jour5StringChiffre = jour5->toString("dd");
    *jour6 = dateCourante->addDays(2);
    jour6String = jour6->toString("dddd");
    jour6StringChiffre = jour6->toString("dd");
    *jour7 = dateCourante->addDays(3);
    jour7String = jour7->toString("dddd");
    jour7StringChiffre = jour7->toString("dd");

    //Déclaration des différents layouts
    layoutMoisAnnee = new QHBoxLayout;
    layoutPrecSuiv = new QHBoxLayout;
    layoutLundi = new QHBoxLayout;
    layoutMardi = new QHBoxLayout;
    layoutMercredi = new QHBoxLayout;
    layoutJeudi = new QHBoxLayout;
    layoutVendredi = new QHBoxLayout;
    layoutSamedi = new QHBoxLayout;
    layoutDimanche = new QHBoxLayout;
    calendarLayout = new QGridLayout;

    //Initialisation du mois et de l'année courants
    QString moisEnCours = dateCourante->toString("MMMM");
    mois = new QLabel("<center>"+moisEnCours+"</center>");
    mois->setFixedWidth(sizeOfWidget/4);
    QString anneeEnCours = dateCourante->toString("yyyy");
    annee = new QLabel("<center>"+anneeEnCours+"</center>");
    annee->setFixedWidth(sizeOfWidget/4);
    precedent = new QPushButton("<");
    precedent->setFixedWidth(sizeOfWidget/2);
    suivant = new QPushButton(">");
    suivant->setFixedWidth(sizeOfWidget/2);

    //Présentation des jours de la semaine
    lundi = new QLabel("<center>"+jour1String+"</center>");
    lundi->setFixedWidth(0.6*sizeOfWidget);
    mardi = new QLabel("<center>"+jour2String+"</center>");
    mardi->setFixedWidth(0.6*sizeOfWidget);
    mercredi = new QLabel("<center>"+jour3String+"</center>");
    mercredi->setFixedWidth(0.6*sizeOfWidget);
    jeudi = new QLabel("<center>"+jour4String+"</center>");
    jeudi->setFixedWidth(0.6*sizeOfWidget);
    vendredi = new QLabel("<center>"+jour5String+"</center>");
    vendredi->setFixedWidth(0.6*sizeOfWidget);
    samedi = new QLabel("<center>"+jour6String+"</center>");
    samedi->setFixedWidth(0.6*sizeOfWidget);
    dimanche = new QLabel("<center>"+jour7String+"</center>");
    dimanche->setFixedWidth(0.6*sizeOfWidget);

    //Initialisation des jours de la semaine
    jourLundi = new QLabel("<center>"+jour1StringChiffre+"</center>");
    jourLundi->setFixedWidth(sizeOfWidget*0.4);
    jourMardi = new QLabel("<center>"+jour2StringChiffre+"</center>");
    jourMardi->setFixedWidth(sizeOfWidget*0.4);
    jourMercredi = new QLabel("<center>"+jour3StringChiffre+"</center>");
    jourMercredi->setFixedWidth(sizeOfWidget*0.4);
    jourJeudi = new QLabel("<center>"+jour4StringChiffre+"</center>");
    jourJeudi->setFixedWidth(sizeOfWidget*0.4);
    jourVendredi = new QLabel("<center>"+jour5StringChiffre+"</center>");
    jourVendredi->setFixedWidth(sizeOfWidget*0.4);
    jourSamedi = new QLabel("<center>"+jour6StringChiffre+"</center>");
    jourSamedi->setFixedWidth(sizeOfWidget*0.4);
    jourDimanche = new QLabel("<center>"+jour7StringChiffre+"</center>");
    jourDimanche->setFixedWidth(sizeOfWidget*0.4);

    // Les rectangles blancs où l'on aura les évènements de la semaine
    lundiEdit = new QTextEdit();
    lundiEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    mardiEdit = new QTextEdit();
    mardiEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    mercrediEdit = new QTextEdit();
    mercrediEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    jeudiEdit = new QTextEdit();
    jeudiEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    vendrediEdit = new QTextEdit();
    vendrediEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    samediEdit = new QTextEdit();
    samediEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);
    dimancheEdit = new QTextEdit();
    dimancheEdit->setFixedSize(sizeOfWidget, 8*sizeOfWidget);

    layoutMoisAnnee->addWidget(mois);
    layoutMoisAnnee->addWidget(annee);
    calendarLayout->addLayout(layoutMoisAnnee, 0, 0);

    layoutPrecSuiv->addWidget(precedent);
    layoutPrecSuiv->addWidget(suivant);
    calendarLayout->addLayout(layoutPrecSuiv, 0, 7);

    layoutLundi->addWidget(lundi);
    layoutLundi->addWidget(jourLundi);
    layoutMardi->addWidget(mardi);
    layoutMardi->addWidget(jourMardi);
    layoutMercredi->addWidget(mercredi);
    layoutMercredi->addWidget(jourMercredi);
    layoutJeudi->addWidget(jeudi);
    layoutJeudi->addWidget(jourJeudi);
    layoutVendredi->addWidget(vendredi);
    layoutVendredi->addWidget(jourVendredi);
    layoutSamedi->addWidget(samedi);
    layoutSamedi->addWidget(jourSamedi);
    layoutDimanche->addWidget(dimanche);
    layoutDimanche->addWidget(jourDimanche);

    calendarLayout->addLayout(layoutLundi, 1, 1);
    calendarLayout->addLayout(layoutMardi, 1, 2);
    calendarLayout->addLayout(layoutMercredi, 1, 3);
    calendarLayout->addLayout(layoutJeudi, 1, 4);
    calendarLayout->addLayout(layoutVendredi, 1, 5);
    calendarLayout->addLayout(layoutSamedi, 1, 6);
    calendarLayout->addLayout(layoutDimanche, 1, 7);

    calendarLayout->addWidget(lundiEdit, 2, 1);
    calendarLayout->addWidget(mardiEdit, 2, 2);
    calendarLayout->addWidget(mercrediEdit, 2, 3);
    calendarLayout->addWidget(jeudiEdit, 2, 4);
    calendarLayout->addWidget(vendrediEdit, 2, 5);
    calendarLayout->addWidget(samediEdit, 2, 6);
    calendarLayout->addWidget(dimancheEdit, 2, 7);

    this->setLayout(calendarLayout);
}


void calendarView::incremente(){
    *jour1 = jour1->addDays(7);
    jour1String = jour1->toString("dddd");
    jour1StringChiffre = jour1->toString("dd");
    lundi->setText("<center>"+jour1String+"</center>");
    jourLundi->setText("<center>"+jour1StringChiffre+"</center>");

    *jour2 = jour2->addDays(7);
    jour2String = jour2->toString("dddd");
    jour2StringChiffre = jour2->toString("dd");
    mardi->setText("<center>"+jour2String+"</center>");
    jourMardi->setText("<center>"+jour2StringChiffre+"</center>");

    *jour3 = jour3->addDays(7);
    jour3String = jour3->toString("dddd");
    jour3StringChiffre = jour3->toString("dd");
    mercredi->setText("<center>"+jour3String+"</center>");
    jourMercredi->setText("<center>"+jour3StringChiffre+"</center>");

    *jour4 = jour4->addDays(7);
    jour4String = jour4->toString("dddd");
    jour4StringChiffre = jour4->toString("dd");
    jeudi->setText("<center>"+jour4String+"</center>");
    jourJeudi->setText("<center>"+jour4StringChiffre+"</center>");

    *jour5 = jour5->addDays(7);
    jour5String = jour5->toString("dddd");
    jour5StringChiffre = jour5->toString("dd");
    vendredi->setText("<center>"+jour5String+"</center>");
    jourVendredi->setText("<center>"+jour5StringChiffre+"</center>");

    *jour6 = jour6->addDays(7);
    jour6String = jour6->toString("dddd");
    jour6StringChiffre = jour6->toString("dd");
    samedi->setText("<center>"+jour6String+"</center>");
    jourSamedi->setText("<center>"+jour6StringChiffre+"</center>");

    *jour7 = jour7->addDays(7);
    jour7String = jour7->toString("dddd");
    jour7StringChiffre = jour7->toString("dd");
    dimanche->setText("<center>"+jour7String+"</center>");
    jourDimanche->setText("<center>"+jour7StringChiffre+"</center>");


    QString moisEnCours = jour4->toString("MMMM");
    mois->setText("<center>"+moisEnCours+"</center>");
    QString anneeEnCours = jour4->toString("yyyy");
    annee->setText("<center>"+anneeEnCours+"</center>");
}

void calendarView::decremente(){
    *jour1 = jour1->addDays(-7);
    jour1String = jour1->toString("dddd");
    jour1StringChiffre = jour1->toString("dd");
    lundi->setText("<center>"+jour1String+"</center>");
    jourLundi->setText("<center>"+jour1StringChiffre+"</center>");

    *jour2 = jour2->addDays(-7);
    jour2String = jour2->toString("dddd");
    jour2StringChiffre = jour2->toString("dd");
    mardi->setText("<center>"+jour2String+"</center>");
    jourMardi->setText("<center>"+jour2StringChiffre+"</center>");

    *jour3 = jour3->addDays(-7);
    jour3String = jour3->toString("dddd");
    jour3StringChiffre = jour3->toString("dd");
    mercredi->setText("<center>"+jour3String+"</center>");
    jourMercredi->setText("<center>"+jour3StringChiffre+"</center>");

    *jour4 = jour4->addDays(-7);
    jour4String = jour4->toString("dddd");
    jour4StringChiffre = jour4->toString("dd");
    jeudi->setText("<center>"+jour4String+"</center>");
    jourJeudi->setText("<center>"+jour4StringChiffre+"</center>");

    *jour5 = jour5->addDays(-7);
    jour5String = jour5->toString("dddd");
    jour5StringChiffre = jour5->toString("dd");
    vendredi->setText("<center>"+jour5String+"</center>");
    jourVendredi->setText("<center>"+jour5StringChiffre+"</center>");

    *jour6 = jour6->addDays(-7);
    jour6String = jour6->toString("dddd");
    jour6StringChiffre = jour6->toString("dd");
    samedi->setText("<center>"+jour6String+"</center>");
    jourSamedi->setText("<center>"+jour6StringChiffre+"</center>");

    *jour7 = jour7->addDays(-7);
    jour7String = jour7->toString("dddd");
    jour7StringChiffre = jour7->toString("dd");
    dimanche->setText("<center>"+jour7String+"</center>");
    jourDimanche->setText("<center>"+jour7StringChiffre+"</center>");


    QString moisEnCours = jour4->toString("MMMM");
    mois->setText("<center>"+moisEnCours+"</center>");
    QString anneeEnCours = jour4->toString("yyyy");
    annee->setText("<center>"+anneeEnCours+"</center>");
}
