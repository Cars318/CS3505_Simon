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
    void gameState(bool isGameRunning);
    void redButtonState(bool isRedButtonOn);
    void progressBarState(int progressBarPercentage);


public slots:
    void changeGameState();
    void changeButtonColor();
    void incrementProgressBar();

private: // Place variables here
    bool isGameRunning;
    bool isRedButtonOn;
    int progressBarPercentage;
    int sequenceLength;

};

#endif // SIMONMODEL_H
