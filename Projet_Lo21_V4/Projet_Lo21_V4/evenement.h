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
    QString description;
    QString lieu;

    friend class ProgManager;
public:
    ProgrammationActivite(const QDate& d, const QTime& h, const QTime& fin, const QString& t,
                          const QString& desc, const QString& l): Evenement(d, h, fin), titre(t), description(desc), lieu(l){}
    QString getDescription() const { return description; }
    QString getLieu() const { return lieu; }

    bool isProgTache() const { return false; }
    QString getTitre() const { return titre; }
};

class ProgrammationTache : public Evenement {

    friend class ProgrammationManager;

protected:
    const TacheUnitaire* tache;

public:
    ProgrammationTache(const QDate& d, const QTime& h,
                       const QTime& fin, const TacheUnitaire& t): Evenement(d, h, fin), tache(&t){}
    const TacheUnitaire& getTache() const { return *tache; }
    virtual bool isProgTache() const { return true; }
    QString getTitre() const { return tache->getTitre(); }

};

class ProgrammationManager {

     friend class ProgrammationTache;

private:
    ProgrammationTache** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(ProgrammationTache* t);
    ProgrammationTache* trouverProgrammationTache(const TacheUnitaire& t) const;
    ProgrammationActivite* trouverProgrammationAct (const ProgrammationActivite& act) const;

public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);

    class Iterator {

            friend class ProgrammationManager;

        private:
            ProgrammationTache** currentProg;
            unsigned int nbRemain;
            Iterator(ProgrammationTache** u, unsigned nb):currentProg(u),nbRemain(nb){}

        public:
            Iterator():nbRemain(0),currentProg(0){}
            bool isDone() const { return nbRemain==0; }
            void next() {
                if (isDone())
                    throw CalendarException("Error, next on an iterator which is done");
                nbRemain--;
                currentProg++;
            }
            ProgrammationTache& current() const {
                if (isDone())
                    throw CalendarException("Error, indirection on an iterator which is done");
                return **currentProg;
            }
        };

        Iterator getIterator() {
            return Iterator(programmations,nb);
        }
};

class EvtPj : public ProgrammationActivite {

private:
    QDate dateFin;

public:
    EvtPj(const QDate& dd, const QTime& hd, const QTime& hf, const QString& t,
          const QString& des, const QString& l, const QDate& df): ProgrammationActivite(dd, hd, hf, t, des, l), dateFin(df){}
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
    Evt1jDur(const QDate& dd, const QTime& hd, const QTime& hf, const QString& t, const QString& des,
          const QString& l, const QTime& dur): ProgrammationActivite(dd, hd, hf, t, des, l), duree(dur) {}
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

#endif // EVENEMENT_H
