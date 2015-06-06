#include "projet.h"

void Projet::ajouterTache(const Tache* t){
    for (int i = 0; i < taches.size(); ++i)
        if (taches[i] == t) throw CalendarException("Tâche déjà existante");
    // ici faire vérif que la tâche n'appartient pas à un autre projet!
    taches.push_back(const_cast<Tache*>(t));
   // ProjetManager::getInstance().projets.insert(t->getId(), this->getTitre());
}

void Projet::suppTache(const Tache* t){
    for (int i = 0; i < taches.size(); ++i){
        if (taches[i] == t){
            taches.erase(taches.begin()+i);
        }
    }
}

//ProjetManager& ProjetManager::getInstance() {
//       if(!instanceUnique) instanceUnique = new ProjetManager();
//       return *instanceUnique;
//}

