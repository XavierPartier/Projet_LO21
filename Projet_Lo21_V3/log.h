#ifndef LOG_H
#define LOG_H

#include "timing.h"
#include "evenement.h"
#include<iostream>

using namespace TIME;

class Log {

public:
    virtual void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s)=0;
    virtual void displayLog(std::ostream& f) const=0;

};

namespace AC { // adaptateur de classe

    class MyLog : public Log, private Agenda {

    public:
        //MyLog():Log(), Agenda() {
        //void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s) {
        //  *this<<Evt1jDur(d,s,h,Duree(0));
            //operator<<(Evt1jDur(d,s,h,Duree(0))); est équivalent
        //}
        void displayLog(std::ostream& f) const {
            Agenda::afficherAgenda(f);
        }
    };

}

namespace AO { // adaptateur d'objet

    class MyLog : public Log {

    private:
        Agenda A;

    public:
        //MyLog():Log(), Agenda() {
        //void addEvt(const TIME::Date& d, const TIME::Horaire& h, const std::string& s) {
        //    A<<Evt1jDur(d,s,h,Duree(0));
            //operator<<(Evt1jDur(d,s,h,Duree(0))); est équivalent
        //}
        void displayLog(std::ostream& f) const {
            A.afficherAgenda(f);
        }
};

class LogError : public std::exception {

private:


public:

};

}

#endif // LOG_H

