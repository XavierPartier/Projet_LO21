#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>

#include "tache.h"

class Projet {

    friend class ProjetManager;

protected:
    QString titre;
    QDate disponibilite;
    QDate echeance;
    std::vector<Tache*> taches;
    int nb;
    int nbMax;

public:
    Projet(const QString& t, const QDate& dispo, const QDate& ech, const std::vector<Tache*> tac): titre(t), disponibilite(dispo), echeance(ech), taches(tac) {}
    ~Projet();

    QString getTitre() const { return titre; }
    void setTitre(const QString& str);
    QDate getDateDispo() const { return disponibilite; }
    QDate getDateEch() const { return echeance; }
    void setDatesDispoEch(const QDate& dispo, const QDate& ech){
        if (ech<dispo) throw CalendarException("erreur Tâche : date echéance avant date dispo");
        for (int i = 0; i < nb; ++i)
            if(ech<taches[i]->getDateEcheance()) throw CalendarException("erreur date échéance projet avant échéance d'une tache");
        disponibilite=dispo;
        echeance=ech;
    }
    QString afficherProjet();
    const std::vector<Tache*>& getTaches() const { return taches; }
    void ajouterTache(const Tache* t);
    void suppTache(const Tache* t);

};

class ProjetManager {

private:

    static ProjetManager* instanceUnique;
    std::vector<Projet*> projets;
    void addItem(Projet* t);
    Projet* trouverProjet(const QString& t) const;
    QString file;


    ~ProjetManager();
    ProjetManager(const ProjetManager& um);

public:

    ProjetManager();

    Projet& ajouterProjet(const QString& t, const QDate& dispo, const QDate& ech, std::vector<Tache*> tac);
    void suppProjet(const QString& titre);
    Projet* getProjet(const QString& t);
    const Projet& getProjet(const QString& t) const;
    static ProjetManager& getInstance();
    bool isProjetExistant(const QString& t) const { return trouverProjet(t)!=0; }
    bool isTacheInProjet(const Tache& t);

    void load(const QString& f);
    void save(const QString& f);

    class iterator {

         friend class TacheManager;
         std::vector<Projet*> currentProjet;
         unsigned int nb;

     public:
         iterator():nb(0),currentProjet(0){}
         iterator(std::vector<Projet*> u):currentProjet(u),nb(0){}
         bool isDone() const { return nb==0; }
         void next() {
             if (isDone())
                 throw CalendarException("error, next on an iterator which is done");
             nb++;
         }
         Projet& current() const {
             if (isDone())
                 throw CalendarException("error, indirection on an iterator which is done");
             return *currentProjet[nb];
         }
     };

     iterator getIterator() {
         return iterator(projets);
     }

 };


#endif // PROJET_H
