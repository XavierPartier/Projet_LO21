#include "tache.h"

using namespace std;

QTextStream& operator<<(QTextStream& fout, const Tache& t){

    fout<<t.getId()<<"\n";
    fout<<t.getTitre()<<"\n";
    fout<<t.getDateDisponibilite().toString()<<"\n";
    fout<<t.getDateEcheance().toString()<<"\n";

    return fout;
}

QString TacheUnitaire::afficherTache() {

    QString text;
    if(this->isPreemptive())
    text.append("Tache unitaire préemptable: \n");
    else
    text.append("Tache unitaire non préemptable: \n");
    text.append("Id: " + this->getId() + "\n");
    text.append("Titre : " + this->getTitre() + "\n");
    Duree d = this->getDuree();
    int x = d.getDureeEnMinutes();
    QString z;
    z.setNum(x);
    text.append("Duree : ");
    text.append(z);
    text.append("\n");
    text.append("Disponibilité : " + this->getDateDisponibilite().toString("dd.MM.yyyy")+ "\n");
    text.append("Echeance : " + this->getDateEcheance().toString("dd.MM.yyyy")+ "\n");

    return text;
}

QString TacheComposite::afficherTache() {

    QString text;
    text.append("Tache composite : \n");
    text.append("Id: " + this->getId() + "\n");
    text.append("Titre : " + this->getTitre() + "\n");
    text.append("Taches composantes : ");
    text.append("Disponibilité : " + this->getDateDisponibilite().toString("dd.MM.yyyy")+ "\n");
    text.append("Echeance : " + this->getDateEcheance().toString("dd.MM.yyyy")+ "\n");
    return text;
}

TacheManager::TacheManager():taches(0),nb(0),nbMax(0){}

void TacheManager::addItem(Tache* t){
    if (nb==nbMax){
        Tache** newtab=new Tache*[nbMax+10];
        for(unsigned int i=0; i<nb; i++) newtab[i]=taches[i];
        // ou memcpy(newtab,taches,nb*sizeof(Tache*));
        nbMax+=10;
        Tache** old=taches;
        taches=newtab;
        delete[] old;
    }
    taches[nb++]=t;
}

Tache* TacheManager::trouverTache(const QString& id) const {
    for(unsigned int i=0; i<nb; i++)
        if (id==taches[i]->getId()) return taches[i];
    return 0;
}

TacheUnitaire& TacheManager::ajouterTacheUnitaire(const QString& id, const QString& t, const QDate& dispo, const QDate& ech, const Duree& dur, bool preempt){
    if (trouverTache(id)) throw CalendarException("erreur, TacheManager, tache deja existante");
    TacheUnitaire* newt= new TacheUnitaire(id, t, dispo, ech, dur, preempt);
    addItem(newt);
    return *newt;
}

TacheComposite& TacheManager::ajouterTacheComposite(const QString& id, const QString& t, const QDate& dispo, const QDate& ech, const vector<Tache*> tc){
    if (trouverTache(id)) throw CalendarException("erreur, TacheManager, tache deja existante");
    TacheComposite* newt= new TacheComposite(id, t, dispo, ech, tc);
    addItem(newt);
    return *newt;
}

void TacheManager::suppTache(const QString& id) {
    if (trouverTache(id)) delete trouverTache(id);
    else throw CalendarException("Tache inexistante");
}

TacheManager::~TacheManager(){
    //if (file!="") save(file);
    for(unsigned int i=0; i<nb; i++) delete taches[i];
    delete[] taches;
    file="";
}

/*
TacheManager& TacheManager::operator=(const TacheManager& um){
    if (this==&um) return *this;
    this->~TacheManager();
    for(unsigned int i=0; i<um.nb; i++) addItem(new Tache(*um.taches[i]));
    return *this;
}
*/

/*
void TacheManager::load(const QString& f){
    if (file!=f) this->~TacheManager();
    file=f;
    ifstream fin(file.c_str()); // open file
    if (!fin) throw CalendarException("erreur, lors de l'ouverture du fichier de taches");
    char tmp[256];
    while (!fin.eof()&&fin.good()){
        fin.getline(tmp,256); // get code
        if (fin.bad()) throw CalendarException("erreur, fichier taches, lecture identificateur tache");
        string id=tmp;
        fin.getline(tmp,256); // get titre
        if (fin.bad()) throw CalendarException("erreur, fichier taches, lecture titre tache");
        string titre=tmp;

        Duree duree;
        fin>>duree;
        if (fin.bad()) throw CalendarException("erreur, fichier taches, lecture duree tache");

        QDate dispo;
        fin>>dispo;
        if (fin.bad()) throw CalendarException("erreur, fichier taches, lecture date disponibilite");

        QDate echeance;
        fin>>echeance;
        if (fin.bad()) throw CalendarException("erreur, fichier taches, lecture date echeance");
        while (fin.peek()=='\r') fin.ignore();
        while (fin.peek()=='\n') fin.ignore();
        std::cout<<"LOAD "<<id<<"-"<<titre<<"-"<<duree<<"-"<<dispo<<"-"<<echeance<<"\n";
        ajouterTache(id,titre,duree,dispo,echeance);
    }
    fin.close(); // close file
}

void  TacheManager::save(const QString& f){
    file=f;
    ofstream fout(f.c_str(),ofstream::trunc); // toutes les taches existantes sont écrasées
    for(unsigned int i=0; i<nb; i++){
        fout<<*taches[i];
    }
    fout.close();
}
*/

TacheManager* TacheManager::instanceUnique=0;

TacheManager& TacheManager::getInstance() {
    if (instanceUnique==0)
        instanceUnique= new TacheManager;
    return *instanceUnique;
}

void TacheManager::libererInstance() {
    if (instanceUnique!=0)
        delete instanceUnique;
    instanceUnique=0;
}
