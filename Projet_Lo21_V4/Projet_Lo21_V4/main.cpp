#include "tache.h"
#include "projet.h"

#include <iostream>
#include <QTextStream>
#include <QApplication>
#include <QMetaType>
#include <fstream>

using namespace std;

int main(int argc, char * argv[]) {

    ofstream monFlux("C:/test.txt");

    std::vector<Tache*> v1, v2;
    int i;
    TacheManager* tm = new TacheManager;
    ProjetManager* pm = new ProjetManager;

    tm->ajouterTacheUnitaire(QString("id1"), QString("titre1"), QDate(2014,6,25), QDate(2014,6,29), Duree(11,50), false);
    tm->ajouterTacheUnitaire(QString("id2"), QString("titre2"), QDate(2014,6,25), QDate(2014,6,29), Duree(11,50), false);
    tm->ajouterTacheUnitaire(QString("id3"), QString("titre3"), QDate(2014,6,25), QDate(2014,6,29), Duree(11,50), false);

    //

    v1.push_back(tm->getTache(QString("id1")));
    v1.push_back(tm->getTache(QString("id2")));
    v1.push_back(tm->getTache(QString("id3")));

    tm->ajouterTacheComposite(QString("tc1"), QString("titre_tc"), QDate(2013,8,8), QDate(2014,1,22), v1);

    v2.push_back(tm->getTache(QString("tc1")));
    std::cout << qPrintable(tm->getTache(QString("tc1"))->afficherTache()) << std::endl;
    Projet p1(QString("p01"), QDate(2014,06,25), QDate(2014,06,29), v2);
    pm->ajouterProjet(QString("p01"), QDate(2014,06,25), QDate(2014,06,29), v2);
    //std::cout << qPrintable(p1.afficherProjet()) << std::endl;

    if(monFlux)
        {
            monFlux << qPrintable(p1.afficherProjet()) << std::endl;
        }
        else
        {
            cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
        }

    return 0;
}
