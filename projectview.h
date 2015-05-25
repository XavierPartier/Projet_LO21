#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>

class projectView : public QWidget{
private:
    QGroupBox *ajoutProjets;
    QGroupBox *listeProjets;
    QGridLayout *layout;
    QHBoxLayout *layoutHautProjet;
    QLineEdit *titreProjet;
    QLineEdit *auteur;
    QSpinBox *nbTaches;

public:
    projectView(QWidget *parent=0);
};

#endif // PROJECTVIEW_H

