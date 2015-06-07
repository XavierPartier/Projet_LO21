#include <QApplication>
#include "fencreaprojet.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    fenCreaProjet fenetre;
    fenetre.show();

    return app.exec();
}
