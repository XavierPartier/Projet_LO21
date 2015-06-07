#include "fencreaprojet.h"

fenCreaProjet::fenCreaProjet() : QWidget() {

    setWindowTitle("Création d'un projet");

    QVBoxLayout *layout0 = new QVBoxLayout;

    QFormLayout *layout1 = new QFormLayout;

    QLineEdit *nomProjet = new QLineEdit(this);

    QListWidget *events = new QListWidget(this);

    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);
    new QListWidgetItem(tr("Oak"), events);
    new QListWidgetItem(tr("Fir"), events);
    new QListWidgetItem(tr("Pine"), events);



    events->setSelectionMode(QAbstractItemView::MultiSelection);

    layout1->addRow("Nom du projet: ", nomProjet);
    layout1->addRow("Liste des évènements: ", events);

    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->setAlignment(Qt::AlignRight);

    QPushButton *creer = new QPushButton("Créer le projet", this);
    QPushButton *annuler = new QPushButton("Annuler la création", this);

    layout2->addWidget(creer);
    layout2->addWidget(annuler);

    layout0->addLayout(layout1);
    layout0->addLayout(layout2);

    setLayout(layout0);

    QObject::connect(annuler, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(creer, SIGNAL(clicked()), this, SLOT(genererCode()));

}

