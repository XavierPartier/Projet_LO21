#include <QApplication>
#include <calendarview.h>
#include "mainview.h"
int main(int argc, char* argv[]) {

    QApplication app(argc, argv);
    //calendarView* cal = new calendarView();
    //cal->show();

    mainView* main = new mainView();
    main->show();
    return app.exec();
}
