#include "evenement.h"

void ProgrammationManager::addItem(ProgrammationTache* t){
    if (nb==nbMax){
        ProgrammationTache** newtab=new ProgrammationTache*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=programmations[i];
        // ou memcpy(newtab,Programmations,nb*sizeof(Programmation*));
        nbMax+=10;
        ProgrammationTache** old=programmations;
        programmations=newtab;
        delete[] old;
    }
    programmations[nb++]=t;
}

ProgrammationTache* ProgrammationManager::trouverProgrammationTache(const TacheUnitaire& t) const{
    for (int i = 0; i < nb; ++i)
        if (programmations[i]->isProgTache())
            if (&t == &(dynamic_cast<ProgrammationTache*>(programmations[i])->getTache())) return dynamic_cast<ProgrammationTache*>(programmations[i]);
    return 0;
}

ProgrammationActivite* ProgrammationManager::trouverProgrammationAct(const ProgrammationActivite& act) const{
    for (int i = 0; i < nb; ++i)
        if (&act == dynamic_cast<ProgrammationActivite*>(programmations[i])) dynamic_cast<ProgrammationActivite*>(programmations[i]);
    return 0;
}
