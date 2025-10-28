#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <QWidget>
#include <QTimer>

class SimonModel : public QObject
{
    Q_OBJECT
public:
    explicit SimonModel(QObject *parent = nullptr);

signals:
    void redButtonState(bool isRedButtonOn);

public slots:
    void changeButtonColor();

private: // Place variables here
    bool isRedButtonOn;

};

#endif // SIMONMODEL_H
