#include "timer.h"
#include <QDebug>
#include <QTimer>

Timer::Timer(QObject *parent)
    : QObject{parent} {
    time = 0;

    // setup signal and slot

}

void Timer::TimerSlot()
{
    timer.start();
}
