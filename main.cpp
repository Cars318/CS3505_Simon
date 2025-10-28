#include "display.h"
#include "timer.h"
#include "simonmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel simon;
    Timer timer;
    Display w(simon);
    w.show();
    return a.exec();
}
