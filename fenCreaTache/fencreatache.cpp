#include "fencreatache.h"

fenCreaTache::fenCreaTache() : QWidget() {

    setWindowTitle("Création d'une tache");

    QVBoxLayout *layout0 = new QVBoxLayout;

    QFormLayout *layout1 = new QFormLayout;

    QLineEdit *id = new QLineEdit(this);
    id->setReadOnly(true);
    id->setFont(QFont("Courier"));

    QLineEdit *titre = new QLineEdit(this);

    QTimeEdit *duree = new QTimeEdit(this);

    QDateEdit *dispo = new QDateEdit(this);
    dispo->setDate(QDate::currentDate());

    QDateEdit *echeance = new QDateEdit(this);
    echeance->setDate(QDate::currentDate());

    layout1->addRow("Identificateur de la tache: ", id);
    layout1->addRow("Titre de la tache: ", titre);
    layout1->addRow("Durée de la tache: ", duree);
    layout1->addRow("Disponibilité de la tache: ", dispo);
    layout1->addRow("Echéance de la tache: ", echeance);


    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->setAlignment(Qt::AlignRight);

    QPushButton *creer = new QPushButton("Créer la tache", this);
    QPushButton *annuler = new QPushButton("Annuler la création", this);

    layout2->addWidget(creer);
    layout2->addWidget(annuler);

    layout0->addLayout(layout1);
    layout0->addLayout(layout2);

    setLayout(layout0);

    QObject::connect(annuler, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(creer, SIGNAL(clicked()), this, SLOT(creerTache()));

}

void fenCreaTache::creerTache() {

}
