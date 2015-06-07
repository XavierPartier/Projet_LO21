#include <QApplication>
#include "fencreatache.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    fenCreaTache fenetre;
    fenetre.show();

    return app.exec();
}

