/**
 * The entry point of the cat application.
 *
 * Team Members:
 *   LAN QUANG HUYNH (GitHub: henrika2)
 *   Cheuk Yin Lau (GitHub: Laconsyn)
 *
 * GitHub Repository: https://github.com/henrika2/assignment6
 *
 * Creative Element:
 *   Animated Button Movement – After each round, the red and blue buttons animate
 *   to new random positions within the main window, adding a playful and dynamic twist
 *   to the game interface.
 *
 */

#include "mainwindow.h"
#include "model.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model m; // This is the only place a Model is created.
    MainWindow w(&m);
    w.show();
    return a.exec();
}
