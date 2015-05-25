#ifndef MAINVIEW_H
#define MAINVIEW_H

#include "calendarview.h"
#include "projectview.h"
#include <QWidget>
#include <QTabWidget>

class mainView : public QWidget{
private:
    calendarView *cal;
    projectView *project;
    QTabWidget *onglets;
public:
    mainView();
};

#endif // MAINVIEW_H

