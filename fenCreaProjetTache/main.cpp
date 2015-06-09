#include <QApplication>
#include "fencreatache.h"
#include "fencreaprojet.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    fenCreaTache fenetre;
    //fenetre.show();

    fenCreaProjet fenetre2;
    fenetre2.show();


    return app.exec();
}


