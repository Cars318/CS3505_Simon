#include "display.h"
#include "simonmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel simon;
    Display w(simon);
    w.show();
    return a.exec();
}
