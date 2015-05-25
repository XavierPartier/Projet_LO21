#include "mainview.h"

mainView::mainView(){
    this->setMinimumSize(1300,900);

    onglets = new QTabWidget(this);
    cal = new calendarView();
    project = new projectView();


    onglets->addTab(cal, "Calendrier");
    onglets->addTab(project, "Projets");
   // onglets->addTab(project, "Evènements");
    //onglets->addTab(project, "Exports");
}
