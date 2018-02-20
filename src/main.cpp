#include <QApplication>
#include "simulation.h"

Simulation *simulation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    simulation = new Simulation();
    simulation->show();
    simulation->displayMenu();

    return a.exec();
}
