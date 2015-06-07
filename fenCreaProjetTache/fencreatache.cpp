#include "fencreatache.h"

fenCreaTache::fenCreaTache() : QWidget() {

    setWindowTitle("Création d'une tache");

    QVBoxLayout *layout0 = new QVBoxLayout;

    QVBoxLayout *layout1 = new QVBoxLayout;

    QVBoxLayout *layout5 = new QVBoxLayout;

    QVBoxLayout *layout6 = new QVBoxLayout;

    QTimeEdit *duree = new QTimeEdit(this);;

    QFormLayout *layout2 = new QFormLayout;
    layout2->addRow("Durée de la tache :", duree);

    QGroupBox *preempTache = new QGroupBox("Tache préemptable: ");
    preempTache->setCheckable(true);
    preempTache->setChecked(false);
    preempTache->setLayout(layout2);

    layout6->addWidget(preempTache);

    QGroupBox *prTaUnitaire = new QGroupBox("Tache unitaire: ");
    prTaUnitaire->setCheckable(true);
    prTaUnitaire->setChecked(false);
    prTaUnitaire->setLayout(layout6);

    layout5->addWidget(prTaUnitaire);

    QGroupBox *typeTache = new QGroupBox("Type de la tache: si la case tache unitaire n'est pas cochée vouz créerez une tache composite.");
    typeTache->setLayout(layout5);

    layout1->addWidget(typeTache);


    QFormLayout *layout3 = new QFormLayout;

    QGroupBox *descTache = new QGroupBox("Description de la tache :");
    descTache->setLayout(layout3);

    QLineEdit *id = new QLineEdit(this);
    //id->setReadOnly(true);
    //id->setFont(QFont("Courier"));

    QLineEdit *titre = new QLineEdit(this);

    QDateEdit *dispo = new QDateEdit(this);
    dispo->setDate(QDate::currentDate());

    QDateEdit *echeance = new QDateEdit(this);
    echeance->setDate(QDate::currentDate());

    layout3->addRow("Identificateur de la tache: ", id);
    layout3->addRow("Titre de la tache: ", titre);
    layout3->addRow("Disponibilité de la tache: ", dispo);
    layout3->addRow("Echéance de la tache: ", echeance);


    QHBoxLayout *layout4 = new QHBoxLayout;
    layout3->setAlignment(Qt::AlignRight);

    QPushButton *creer = new QPushButton("Créer la tache", this);
    QPushButton *annuler = new QPushButton("Annuler la création", this);

    layout4->addWidget(creer);
    layout4->addWidget(annuler);

    layout0->addLayout(layout1);
    layout0->addWidget(descTache);
    layout0->addLayout(layout4);

    setLayout(layout0);

    QObject::connect(annuler, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(creer, SIGNAL(clicked()), this, SLOT(creerTache()));

}

void fenCreaTache::creerTache() {

}
