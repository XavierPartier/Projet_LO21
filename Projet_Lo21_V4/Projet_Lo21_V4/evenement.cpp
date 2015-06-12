#include "evenement.h"


EvenementManager::EvenementManager():programmations(0),nb(0),nbMax(0){}

EvenementManager::~EvenementManager(){
    //if (file!="") save(file);
    for(unsigned int i=0; i<nb; i++) delete programmations[i];
    delete[] programmations;
    file="";
}

void EvenementManager::addItem(Evenement* t){
    if (nb==nbMax){
        Evenement** newtab=new Evenement*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        Evenement** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=t;
}

/*ProgrammationTache* EvenementManager::trouverProgrammation(const TacheUnitaire& t) const{
    for (int i = 0; i < nb; ++i)
            if (t.getId() == &(dynamic_cast<ProgrammationTache*>(programmations[i])->getTache().getId())) return dynamic_cast<ProgrammationTache*>(programmations[i]);
    return 0;
}*/

/*void ProgrammationActManager::addItem(ProgrammationActivite* t){
    if (nb==nbMax){
        ProgrammationActivite** newtab=new ProgrammationActivite*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        ProgrammationActivite** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=t;
}*/

ProgrammationActivite* EvenementManager::trouverProgrammation(const ProgrammationActivite& act) const{
    for (int i = 0; i < nb; ++i)
        if (&act == dynamic_cast<ProgrammationActivite*>(programmations[i])) return dynamic_cast<ProgrammationActivite*>(programmations[i]);
    return 0;
}

ProgrammationTache& EvenementManager::ajouterProgrammation(const QDate& d, const QTime& h,const QTime& fin, TacheUnitaire& t) {
    //if(trouverProgrammation(t))
    //    throw CalendarException("Evenement deja existant");
    if (t.getDateDisponibilite()> d)
        throw CalendarException ("La tache n'est pas disponible pour cette date");
    if (t.getDateEcheance()< d)
        throw CalendarException("Léchéance de la tâche est avant cette date");
    if(trouverDateEvt(d))
        throw CalendarException("Un évènement est déjà programmé à cette date!");
    ProgrammationTache* newt= new ProgrammationTache(d, h, fin, t);
    addItem(newt);
    return *newt;

}

EvtPj& EvenementManager::ajouterProgrammation(const EvtPj& e){
    //if(trouverProgrammation(e))
    //    throw CalendarException("Evenement deja existant");
    if(trouverDateEvt(e))
        throw CalendarException("Un évènement est déjà programmé à cette date!");
    EvtPj* newt= new EvtPj(e);
    addItem(newt);
    return *newt;
}

Evt1jDur& EvenementManager::ajouterProgrammation(const Evt1jDur& e){
    if(trouverProgrammation(e))
        throw CalendarException("Evenement deja existant");
    if(trouverDateEvt(e))
        throw CalendarException("Un évènement est déjà programmé à cette date!");
    Evt1jDur* newt= new Evt1jDur(e);
    addItem(newt);
    return *newt;
}

ProgrammationTache* EvenementManager::trouverDateEvt(const QDate& d) const{
    for (int i = 0; i < nb; ++i)
        if (d == programmations[i]->getDate()) return dynamic_cast<ProgrammationTache*>(programmations[i]) ;
    return 0;
}

ProgrammationActivite* EvenementManager::trouverDateEvt(const Evenement& e) const{
    for (int i = 0; i < nb; ++i)
        if (e.getDate() == programmations[i]->getDate()) return dynamic_cast<ProgrammationActivite*>(programmations[i]);
    return 0;
}
