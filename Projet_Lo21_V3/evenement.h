#if !defined(_EVENEMENT_H)
#define _EVENEMENT_H

#include <iostream>
#include <string>
#include <sstream>

#include "timing.h"

namespace TIME{

class Evt {

private:
    std::string sujet;

public:
    Evt(const std::string& s):sujet(s){}
    const std::string& getDescription() const { return sujet; }
    void afficher(std::ostream& f) const { f<<toString(); }
    virtual std::string toString() const=0;
    virtual ~Evt(){}
    virtual Evt* clone() const=0;

};

class EvtPj : public Evt {

private:
    Date dateDebut;
    Date dateFin;

public:
    EvtPj(const Date& deb, const Date& fin, const std::string s): Evt(s), dateDebut(deb), dateFin(fin){
        std::cout<<this<<"Construction de l'objet EvtPj "<<getDescription()<<std::endl;
    }
    const Date& getDateDebut() const { return dateDebut; }
    const Date& getDateFin() const { return dateFin; }
    /*virtual void afficher(std::ostream& f= std::cout) const override {
        f<<"***** Evt ********"<<"\n"<<"Date debut= "<<dateDebut<<" Date fin= "<<dateFin<<" sujet= "<<getDescription()<<"\n";
    }*/
    std::string toString() const {
        std::stringstream f;
        f<<" ***** Evt ***** "
        <<"\n"<<"Date debut= "<<dateDebut<<" Date fin= "<<dateFin
        <<" Sujet= "<<getDescription()<<"\n";
        return f.str();
    }
    ~EvtPj() {
        std::cout<<"Destruction de l'objet EvtPj "<<getDescription()<<std::endl;}
    EvtPj* clone() const {return new EvtPj(*this);}
};

class Evt1j : public Evt {

private:
    Date date;

public:
    Evt1j(const Date& d, const std::string& s):Evt(s),date(d){std::cout<<"Construction de l'objet Evt1j "<<getDescription()<<std::endl;}
    const Date& getDate() const { return date; }
    /*virtual void afficher(std::ostream& f= std::cout) const override {
    f<<"***** Evt ********"<<"\n"<<"Date="<<date<<" sujet="<<getDescription()<<"\n";
    }*/
    std::string toString() const {
        std::stringstream f;
        f<<" ***** Evt ***** "
        <<"\n"<<"Date= "<<date
        <<" Sujet="<<getDescription()<<"\n";
        return f.str();
    }
    ~Evt1j() {
        std::cout<<"Destruction de l'objet Evt1j "<<getDescription()<<std::endl;}
    Evt1j* clone() const {return new Evt1j(*this);}
};

class Evt1jDur: public Evt1j {

private:
    Horaire debut;
    Duree duree;

public:
    Evt1jDur(const Date& date, const std::string& s, const Horaire& debut, const Duree& duree):Evt1j(date, s), debut(debut), duree(duree){std::cout<<"Construction de l'objet Evt1jDur "<<getDescription()<<std::endl;}
    const Horaire& getDebut() const { return this->debut; }
    const Duree& getDuree() const { return this->duree; }
    /*void afficher(std::ostream& f= std::cout) const override {
        Evt1j::afficher(f);
        this->debut.afficher(f);
        this->duree.afficher(f);
    }*/
    std::string toString() const {
        std::stringstream f;
        f<<Evt1j::toString();
        f<<"Horaire= "<<debut<<" Duree= "<<duree<<"\n";
        return f.str();
    }
    ~Evt1jDur() {
        std::cout<<"Destruction de l'objet Evt1jDur "<<getDescription()<<std::endl;}
    Evt1jDur* clone() const {return new Evt1jDur(*this);}
};

class RDV: public Evt1jDur {

private:
    std::string lieu;
    std::string personnes;

public:
    RDV(const Date& date, const std::string& s, const Horaire& debut, const Duree& duree, const std::string& lieu, const std::string& personnes):Evt1jDur(date, s, debut, duree), lieu(lieu), personnes(personnes){std::cout<<"Construction de l'objet RDV "<<getDescription()<<std::endl;}
    RDV(const RDV& r): Evt1jDur(r.getDate(), r.getDescription(), r.getDebut(), r.getDuree()), lieu(r.lieu), personnes(r.personnes) {}
    RDV& operator=(const RDV& r){
    /*  this->lieu = r.lieu;
      this->personnes = r.personnes;
     Evt1jDur *x = this;
        *x = r; */

        *this = r;
    }
    const std::string& getLieu() const { return this->lieu; }
    const std::string& getPersonnes() const { return this->personnes; }
    /*void afficher(std::ostream& f= std::cout) const override {
        Evt1jDur::afficher(f);
        f<<"Lieu="<<this->lieu<<std::endl
        <<"Personnes="<<this->personnes<<std::endl;
    }*/
    std::string toString() const {
        std::stringstream f;
        f<<Evt1jDur::toString();
        f<<"Lieu= "<<lieu<<" Personnes= "<<personnes<<"\n";
    }

    ~RDV() {
        std::cout<<"Destruction de l'objet RDV "<<getDescription()<<std::endl;}
    RDV* clone() const {return new RDV(*this);}
};

class Agenda {

private:
    Evt** tab;
    int nb, nbMax;
public:
    Agenda(int nb, int nbMax): nb(nb), nbMax(nbMax){
        tab = new Evt*[10];
    }

    //Agenda& operator<<(Evt& e){
    //    Evt* nevt=e.clone();
    //}
    virtual ~Agenda() {
        for(int i=0; i<nb; i++)
            delete tab[i];
    }
    void afficherAgenda(std::ostream& f = std::cout) const {
        for(int i=0; i<nb; i++)
            tab[i]->afficher(f);
        }

    class Iterator {

    private:
        Evt** pt;

    public:
        Iterator(Evt** e): pt(e){}
        Iterator& operator++() {pt++; return *this;}
        Evt& operator*() const {return **pt;}
        bool operator!=(Iterator it) const {return pt!=it.pt;}
        Iterator& operator--() {pt--; return *this;}
    };

    Iterator begin() const {return Iterator(tab);}
    Iterator end() const {return Iterator(tab+nb);}

};


std::ostream& operator <<(std::ostream& f, const Evt& j) {
    j.afficher(f);
    return f;
}
}


#endif

