#ifndef FENCREATACHE_H
#define FENCREATACHE_H


#include <QtWidgets>

class fenCreaTache : public QWidget {

    Q_OBJECT

private:
    QLineEdit *id;
    QLineEdit *titre;
    QTimeEdit *duree;
    QDateEdit *dispo;
    QDateEdit *echeance;

public slots:
    void creerTache();

public:
    fenCreaTache();

};

#endif // FENCREATACHE_H
