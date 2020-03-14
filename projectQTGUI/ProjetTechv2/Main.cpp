#include <QApplication>
#include <QtWidgets>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow Fenetre;
    Fenetre.show();

    return app.exec();
}
