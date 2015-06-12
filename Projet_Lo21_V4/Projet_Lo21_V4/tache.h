#ifndef TACHE_H
#define TACHE_H

#include <QString>
#include <QDate>
#include <iostream>

#include "duree.h"

class CalendarException{
public:
    CalendarException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
};


class Tache { //classe abstraite

friend class TacheManager;

protected:

    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    //Tache(const QString& id, const QString& t, const QDate& dispo, const QDate& ech):
    //      identificateur(id),titre(t), disponibilite(dispo),echeance(ech){}

public:

    Tache(const QString& id, const QString& t, const QDate& dispo, const QDate& ech): // à ne laisser que dans le protected!
            identificateur(id),titre(t), disponibilite(dispo),echeance(ech){}
    QString getId() const { return identificateur; }
    QString getTitre() const { return titre; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    virtual bool isTacheUnitaire() const =0;
    virtual QString afficherTache() =0;
    void setTitre(const QString& str);
    void setId(const QString& str) { identificateur=str; }
    void setDatesDispoEch(const QDate& disp, const QDate& ech){
        if (ech<disp) throw CalendarException("erreur Tâche : date echéance avant date dispo");
        disponibilite=disp; echeance=ech;
    }
     virtual ~Tache(){}
};

class TacheUnitaire : public Tache{

    friend class TacheManager;

private:
    Duree duree;
    bool preemptive;


public:
    TacheUnitaire(const QString& id, const QString& titre, const QDate& dispo, const QDate& ech, const Duree& dur, bool preempt=false):
            Tache(id, titre, dispo, ech), duree(dur), preemptive(preempt){
        if (!preempt && dur.getDureeEnHeures()>12) throw CalendarException("erreur tâche unitaire non preemptive et durée > 12h");
    }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    bool isPreemptive() const { return preemptive; }
    void setPreemptive(bool b = true) { preemptive=b; }
    void ajouterInfos(QString& infos) const;
    bool isTacheUnitaire() const { return true; }
    virtual QString afficherTache() ;
};


class TacheComposite : public Tache{

    friend class TacheManager;

private:
    std::vector<Tache*> tachesComposantes;
    TacheComposite(const QString& id, const QString& t, const QDate& dispo, const QDate& ech, const std::vector<Tache*> tc):
    Tache(id, t, dispo, ech), tachesComposantes(tc) {}
    TacheComposite(const QString& id, const QString& t, const QDate& dispo, const QDate& ech):
    Tache(id, t, dispo, ech) {}
public:
    const std::vector<Tache*> getTachesComposantes() const { return tachesComposantes; }
    void ajoutTacheComposante(Tache* tache);
    void suppTacheComposante(const QString& nom);
    void setTachesComposantes(const std::vector<Tache*> tc);
    Tache& getTacheComposante(const QString& id);
    std::vector<Tache*>& getTachesComposantes() { return tachesComposantes; }
    void ajouterInfos(QString& infos) const;
    bool isTacheUnitaire() const { return false; }
    virtual QString afficherTache() ;

};

class TacheManager {

private:

    static TacheManager* instanceUnique;

    Tache** taches;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Tache* t);
    Tache* trouverTache(const QString& t) const;
    QString file;


    ~TacheManager();
    TacheManager(const TacheManager& um);

public:

    TacheManager();

    static TacheManager& getInstance();
    static void libererInstance();

    TacheManager& operator=(const TacheManager& um);
    TacheUnitaire& ajouterTacheUnitaire(const QString& id, const QString& t, const QDate& dispo, const QDate& ech, const Duree& dur, bool preempt=false);
    TacheComposite& ajouterTacheComposite(const QString& identificateur, const QString& titre, const QDate& disponibilite, const QDate& echeance, const std::vector<Tache*> tc);
    TacheComposite& ajouterTacheComposite(const QString& identificateur, const QString& titre, const QDate& disponibilite, const QDate& echeance);
    void suppTache(const QString& id);
    Tache* getTache(const QString& id) ;
    const Tache& getTache(const QString& id) const;
    bool isTacheExistante (const QString& id) const { return trouverTache(id)!=0; }
    void load(const QString& f);
    void save(const QString& f);

    class iterator {

         friend class TacheManager;
         Tache** currentTache;
         unsigned int nbRemain;
         iterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}

     public:
         iterator():nbRemain(0),currentTache(0){}
         bool isDone() const { return nbRemain==0; }
         void next() {
             if (isDone())
                 throw CalendarException("error, next on an iterator which is done");
             nbRemain--;
             currentTache++;
         }
         Tache& current() const {
             if (isDone())
                 throw CalendarException("error, indirection on an iterator which is done");
             return **currentTache;
         }
     };

     iterator getIterator() {
         return iterator(taches,nb);
     }

 };



QTextStream& operator<<(QTextStream& f, const Tache& t);

#endif // TACHE_H
