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

QString Projet::afficherProjet() {

    int i;
    QString text;
    text.append(this->getTitre() + ";");
    for (i=0; i<taches.size(); i++) {
        text.append(taches[i]->getId() + ";");
        /*if(taches[i]->isTacheUnitaire() == false){
            std::vector<Tache*> vec = dynamic_cast<TacheComposite&>(taches[i])->getTachesComposantes();
            for(int j=0; j<vec.size(); j++) {
                text.append(",");
                text.append(vec[j]->getId());
            }
        }
        else
            text.append(";");
*/
        }
    text.append(this->getDateDispo().toString("dd.MM.yyyy")+ ";");
    text.append(this->getDateEch().toString("dd.MM.yyyy")+ ";");

    return text;
}


Projet::~Projet() {
    taches.clear();
}

Projet& ProjetManager::ajouterProjet(const QString& t, const QDate& dispo, const QDate& ech, std::vector<Tache*> tac){
    if (isProjetExistant(t)) throw CalendarException("Projet deja existant");
    Projet* newt= new Projet(t, dispo, ech, tac);
    addItem(newt);
    return *newt;
}

ProjetManager::ProjetManager(){
        projets.reserve(10);
    }

void ProjetManager::addItem(Projet *pro) {
    projets.push_back(pro);
}

Projet* ProjetManager::getProjet(const QString& t){
    Projet* pro=trouverProjet(t);
    if (!pro) throw CalendarException("Projet inexistant");
    return pro;
}

Projet* ProjetManager::trouverProjet(const QString &t) const {
    for(unsigned int i=0; projets.size(); i++)
        if (t==projets[i]->getTitre()) return projets[i];
    return 0;
}

ProjetManager::~ProjetManager(){
    //if (file!="") save(file);
    projets.clear();
    file="";
}
/*ProjetManager& ProjetManager::getInstance() {
    if (instanceUnique==0)
        instanceUnique= new ProjetManager;
    return *instanceUnique;
}*/

