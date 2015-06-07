#ifndef CALENDAR_h
#define CALENDAR_h
#include<string>
#include<iostream>
#include "timing.h"
using namespace std;
using namespace TIME;


class CalendarException{
public:
    CalendarException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};

class Tache {

friend class TacheManager;

    string identificateur;
    string titre;
    Duree duree;
    Date disponibilite;
    Date echeance;
    Tache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline){}
public:

    string getId() const { return identificateur; }
    string getTitre() const { return titre; }
    Duree getDuree() const { return duree; }
    Date getDateDisponibilite() const {  return disponibilite; }
    Date getDateEcheance() const {  return echeance; }
};

class TacheManager {

private:

    static TacheManager* instanceUnique;

    Tache** taches;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Tache* t);
    Tache* trouverTache(const string& id) const;
    string file;

    TacheManager();
    ~TacheManager();
    TacheManager(const TacheManager& um);

public:

    static TacheManager& getInstance();
    static void libererInstance();

    TacheManager& operator=(const TacheManager& um);
    Tache& ajouterTache(const string& id, const string& t, const Duree& dur, const Date& dispo, const Date& deadline);
    Tache& getTache(const string& id);
    const Tache& getTache(const string& code) const;
    void load(const string& f);
    void save(const string& f);

    class Iterator {
        friend class TacheManager;
        Tache** currentTache;
        unsigned int nbRemain;
        Iterator(Tache**u, unsigned nb): currentTache(u), nbRemain(nb) {}

        public:
            Iterator(): nbRemain(0),currentTache(0){}

            bool isDone() const {return nbRemain==0; }

            void next() {
                if (isDone())
                    throw CalendarException ("Error, next on an iterator which is done");
                nbRemain --;
                currentTache ++;
            }

            Tache& current() const {
                if (isDone())
                    throw CalendarException ("Error, indirection on an iterator which is done");
                return **currentTache;
            }
};

Iterator getIterator() {
    return Iterator(taches, nb);
}
};


class Programmation {
    const Tache* tache;
    Date date;
    Horaire horaire;
public:
    Programmation(const Tache& t, const Date& d, const Horaire& h):tache(&t), date(d), horaire(h){}
    const Tache& getTache() const { return *tache; }
    Date getDate() const { return date; }
    Horaire getHoraire() const { return horaire; }
};

class ProgrammationManager {
private:
    Programmation** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;
public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    void ajouterProgrammation(const Tache& t, const Date& d, const Horaire& h);
};

ostream& operator<<(ostream& f, const Tache& t);
ostream& operator<<(ostream& f, const Programmation& p);


#endif
