#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>

#include "duree.h"
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
    const std::vector<Tache*>& getTaches() const { return taches; }
    void ajouterTache(const Tache* t);
    void suppTache(const Tache* t);

};

class ProjetManager {

private:

    static ProjetManager* instanceUnique;
    Projet** projets;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Projet* t);
    Projet* trouverProjet(const QString& id) const;
    QString file;


    ~ProjetManager();
    ProjetManager(const ProjetManager& um);

public:

    ProjetManager();

    Projet& ajouterProjet(const QString& t, const QDate& dispo, const QDate& ech);
    void suppProjet(const QString& titre);
    Projet& getProjet(const QString& id);
    const Projet& getProjet(const QString& id) const;
    static ProjetManager& getInstance();
    bool isProjetExistant(const QString& id) const { return trouverProjet(id)!=0; }
    bool isTacheInProjet(const Tache& t);

    void load(const QString& f);
    void save(const QString& f);

    class iterator {

         friend class TacheManager;
         Projet** currentProjet;
         unsigned int nbRemain;

     public:
         iterator():nbRemain(0),currentProjet(0){}
         iterator(Projet** u, unsigned nb):currentProjet(u),nbRemain(nb){}
         bool isDone() const { return nbRemain==0; }
         void next() {
             if (isDone())
                 throw CalendarException("error, next on an iterator which is done");
             nbRemain--;
             currentProjet++;
         }
         Projet& current() const {
             if (isDone())
                 throw CalendarException("error, indirection on an iterator which is done");
             return **currentProjet;
         }
     };

     iterator getIterator() {
         return iterator(projets,nb);
     }

 };


#endif // PROJET_H
