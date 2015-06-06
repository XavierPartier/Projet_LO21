#ifndef DUREE_H
#define DUREE_H

#include<iostream>
#include<iomanip>
#include<QTextStream>

class TimeException{

public:
    TimeException(const std::string& m):info(m){}
    const std::string& GetInfo() const { return info; }

private:
    std::string info;
};

class Duree{

public:
    Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw TimeException("erreur: initialisation duree invalide");}
    Duree(unsigned int m=0):nb_minutes(m) {}
    void setDuree(unsigned int heures, unsigned int minutes) { if (minutes>59) throw TimeException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
    unsigned int getDureeEnMinutes() const { return nb_minutes; } //<!Retourne la duree en minutes
    double getDureeEnHeures() const { return double(nb_minutes)/60; } //<!Retourne la duree en heures
    unsigned int getMinute() const { return nb_minutes%60; }
    unsigned int getHeure() const { return nb_minutes/60; }
    void afficher(QTextStream& f) const;

private:
    unsigned int nb_minutes;
};

QTextStream& operator<<(QTextStream& f, const Duree & d);
QTextStream& operator>>(QTextStream& flot , Duree& d);

#endif // DUREE_H
