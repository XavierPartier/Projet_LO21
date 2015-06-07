#ifndef FENCREAPROJET_H
#define FENCREAPROJET_H

#include <QtWidgets>

class fenCreaProjet : public QWidget {

private:
    QLineEdit *nomProjet;
    QListView *events;
    QPushButton *creer;
    QPushButton *annuler;

public:
    fenCreaProjet();

};

#endif // FENCREAPROJET_H
