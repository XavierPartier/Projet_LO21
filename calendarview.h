#ifndef CALENDARVIEW
#define CALENDARVIEW

#include <QWidget>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QTextEdit>
#include <QDate>

class calendarView : public QWidget{
    Q_OBJECT

private:
    QGridLayout *calendarLayout;
    QHBoxLayout *layoutPrecSuiv;
    QHBoxLayout *layoutMoisAnnee;
    QHBoxLayout *layoutLundi;
    QHBoxLayout *layoutMardi;
    QHBoxLayout *layoutMercredi;
    QHBoxLayout *layoutJeudi;
    QHBoxLayout *layoutVendredi;
    QHBoxLayout *layoutSamedi;
    QHBoxLayout *layoutDimanche;
    QLabel *mois;
    QLabel *annee;
    QPushButton *precedent;
    QPushButton *suivant;
    QLabel *lundi;
    QLabel *mardi;
    QLabel *mercredi;
    QLabel *jeudi;
    QLabel *vendredi;
    QLabel *samedi;
    QLabel *dimanche;
    QLabel *jourLundi;
    QLabel *jourMardi;
    QLabel *jourMercredi;
    QLabel *jourJeudi;
    QLabel *jourVendredi;
    QLabel *jourSamedi;
    QLabel *jourDimanche;
    QTextEdit *lundiEdit;
    QTextEdit *mardiEdit;
    QTextEdit *mercrediEdit;
    QTextEdit *jeudiEdit;
    QTextEdit *vendrediEdit;
    QTextEdit *samediEdit;
    QTextEdit *dimancheEdit;
    QDate *dateCourante;
    QDate *jour1;
    QDate *jour2;
    QDate *jour3;
    QDate *jour4;
    QDate *jour5;
    QDate *jour6;
    QDate *jour7;
    QString jour1String;
    QString jour2String;
    QString jour3String;
    QString jour4String;
    QString jour5String;
    QString jour6String;
    QString jour7String;
    QString jour1StringChiffre;
    QString jour2StringChiffre;
    QString jour3StringChiffre;
    QString jour4StringChiffre;
    QString jour5StringChiffre;
    QString jour6StringChiffre;
    QString jour7StringChiffre;

public:
    calendarView();
    void initialise();

public slots:
    void incremente();
    void decremente();
};


#endif // CALENDARVIEW

