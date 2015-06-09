<<<<<<< HEAD
#include "tache.h"

#include <iostream>
#include <QTextStream>
#include <QApplication>
#include <QMetaType>

using namespace std;

int main(int argc, char * argv[]) {

    TacheManager* tm = new TacheManager;

    tm->ajouterTacheUnitaire(QString("id1"), QString("titre1"), QDate(2014,06,25), QDate(2014,06,29), Duree(11,50), false);
    tm->ajouterTacheUnitaire(QString("id2"), QString("titre2"), QDate(2014,06,25), QDate(2014,06,29), Duree(11,50), false);

    for(TacheManager::iterator it=tm->getIterator(); !it.isDone(); it.next()) it.current().afficherTache();
    //Evt1jDur e3(Date(11,6,2013),"Lancement de Longue Marche",Horaire(17,38),Duree
    //(0,10));

    //tu.afficherTache();

    return 0;
=======
#include <QApplication>
#include <calendarview.h>
#include "mainview.h"
int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    //calendarView* cal = new calendarView();
    //cal->show();

    mainView* main = new mainView();
    main->show();
    return app.exec();
>>>>>>> b05d34aeb95f3f675ef565b4d9d57ade368416d5
}
