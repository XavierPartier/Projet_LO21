#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QDate>

#include "tache.h"

class Evenement{ // classe abstraite
private:
    QDate date;
    QTime horaire;
    QTime horaireFin;

public:
    Evenement(const QDate& d, const QTime& h, const QTime& fin): date(d), horaire(h), horaireFin(fin){}
    virtual ~Evenement(){}

    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
    QTime getHoraireFin() const { return horaireFin; }

    virtual bool isProgTache() const =0;
    virtual QString getTitre() const =0;

};



class ProgrammationActivite : public Evenement {
private:
    QString titre;
    //QString description;
    QString lieu;

    friend class EvenementManager;

public:
    ProgrammationActivite(const QDate& d, const QTime& h, const QTime& fin, const QString& t,
                          const QString& l): Evenement(d, h, fin), titre(t), lieu(l){}
    //QString getDescription() const { return description; }
    QString getLieu() const { return lieu; }

    bool isProgTache() const { return false; }
    QString getTitre() const { return titre; }

};

class ProgrammationTache : public Evenement {

    friend class EvenementManager;

protected:
    const TacheUnitaire* tache;

public:
    ProgrammationTache(const QDate& d, const QTime& h,
                       const QTime& fin, const TacheUnitaire& t): Evenement(d, h, fin), tache(&t){}
    const TacheUnitaire& getTache() const { return *tache; }
    virtual bool isProgTache() const { return true; }
    QString getTitre() const { return tache->getTitre(); }

};

class EvtPj : public ProgrammationActivite {

private:
    QDate dateFin;

public:
    EvtPj(const QDate& dd, const QTime& hd, const QTime& hf, const QString& t,
          const QString& l, const QDate& df): ProgrammationActivite(dd, hd, hf, t, l), dateFin(df){}
    const QDate& getDate() const;
    const QDate& getDateFin() const { return dateFin; }
    /*virtual void afficher(std::ostream& f= std::cout) const override {
        f<<"***** Evt ********"<<"\n"<<"Date debut= "<<dateDebut<<" Date fin= "<<dateFin<<" sujet= "<<getDescription()<<"\n";
    }*/
    /*QString toString() const {
        std::stringstream f;
        f<<" ***** Evt ***** "
        <<"\n"<<"Date debut= "<<dateDebut<<" Date fin= "<<dateFin
        <<" Sujet= "<<getDescription()<<"\n";
        return f.str(); ]}*/

    ~EvtPj() {}
    EvtPj* clone() const {return new EvtPj(*this);}
};


class Evt1jDur : public ProgrammationActivite {

private:
    QTime duree;

public:
    Evt1jDur(const QDate& dd, const QTime& hd, const QTime& hf, const QString& t,
          const QString& l, const QTime& dur): ProgrammationActivite(dd, hd, hf, t, l), duree(dur) {}
    const QTime& getDuree() const { return duree; }
    /*virtual void afficher(std::ostream& f= std::cout) const override {
    f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<getDescription()<<"\n";
    }*/
    /*std::string toString() const {
        std::stringstream f;
        f<<" ***** Evt ***** "
        <<"\n"<<"Date= "<<date
        <<" Sujet="<<getDescription()<<"\n";
        return f.str();
    }*/
    ~Evt1jDur() {}
    Evt1jDur* clone() const {return new Evt1jDur(*this);}
};


class EvenementManager {

     friend class ProgrammationTache;
     friend class ProgrammationActivite;

private:
    Evenement** programmations;
    unsigned int nb;
    unsigned int nbMax;
    QString file;
    void addItem(Evenement* t);
    ProgrammationTache* trouverProgrammation(const TacheUnitaire& t) const;
    ProgrammationTache* trouverDateEvt(const QDate& d) const;
    //void addItem(ProgrammationActivite* t);
    ProgrammationActivite* trouverProgrammation (const ProgrammationActivite& act) const;
    ProgrammationActivite* trouverDateEvt(const Evenement& e) const;


public:
    EvenementManager();
    ~EvenementManager();
    EvenementManager(const EvenementManager& um);
    EvenementManager& operator=(const EvenementManager& um);
    ProgrammationTache& ajouterProgrammation(const QDate& d, const QTime& h,const QTime& fin, TacheUnitaire& t);
    EvtPj& ajouterProgrammation(const EvtPj& e);
    Evt1jDur& ajouterProgrammation(const Evt1jDur& e);

    class Iterator {

            friend class EvenementManager;

        private:
            Evenement** currentProg;
            unsigned int nbRemain;
            Iterator(Evenement** u, unsigned nb):currentProg(u),nbRemain(nb){}

        public:
            Iterator():nbRemain(0),currentProg(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw CalendarException("Error, next on an iterator which is done");
                nbRemain--;
                currentProg++;
            }
            Evenement& current() const {
                if (isDone())
                    throw CalendarException("Error, indirection on an iterator which is done");
                return **currentProg;
            }
        };

        Iterator getIterator() {
            return Iterator(programmations,nb);
        }
};


/*class ProgrammationActManager {

     friend class ProgrammationActivite;

private:
    ProgrammationActivite** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(ProgrammationActivite* t);
    ProgrammationActivite* trouverProgrammationAct (const ProgrammationActivite& act) const;
    ProgrammationActivite* trouverDateEvt(const Evenement& e) const;

public:
    ProgrammationActManager();
    ~ProgrammationActManager();
    ProgrammationActManager(const EvenementManager& um);
    ProgrammationActManager& operator=(const ProgrammationActManager& um);
    EvtPj& ajouterProgrammationAct(const EvtPj& e);
    Evt1jDur& ajouterProgrammationAct(const Evt1jDur& e);

    class Iterator {

            friend class ProgrammationActManager;

        private:
            ProgrammationActivite** currentProg;
            unsigned int nbRemain;
            Iterator(ProgrammationActivite** u, unsigned nb):currentProg(u),nbRemain(nb){}

        public:
            Iterator():nbRemain(0),currentProg(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw CalendarException("Error, next on an iterator which is done");
                nbRemain--;
                currentProg++;
            }
            ProgrammationActivite& current() const {
                if (isDone())
                    throw CalendarException("Error, indirection on an iterator which is done");
                return **currentProg;
            }
        };

        Iterator getIterator() {
            return Iterator(programmations,nb);
        }
};*/


#endif // EVENEMENT_H
