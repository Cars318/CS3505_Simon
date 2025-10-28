#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>

class Timer : public QObject
{
    Q_OBJECT
public:
    explicit Timer(QObject *parent = nullptr);


signals:
    void TimerSignal(int time);

public slots:
    void TimerSlot();

private:
    int time;
    QTimer timer;


};

#endif // TIMER_H
