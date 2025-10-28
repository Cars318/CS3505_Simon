#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <QWidget>
#include <QTimer>
#include <QVector>

class SimonModel : public QObject
{
    Q_OBJECT
public:
    explicit SimonModel(QObject *parent = nullptr);

signals:
    void flashRed();
    void flashBlue();
    void flashingStateChanged(int buttonToFlash, bool isFlashing);
    void updateSequence(QVector<int> sequence);
    void gameState(bool isGameRunning);
    void redButtonState(bool isRedButtonOn);
    void progressBarState(int progressBarPercentage);
    void startButtonState(bool isStartButtonActive);

public slots:
    void handleTimeout();
    void startGame();
    void changeButtonColor();
    void incrementProgressBar();

private: // Place variables here
    QList<int> sequenceList;

    bool isFlashing;
    bool isGameRunning;
    bool isStartButtonActive;
    bool isRedButtonOn;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceLength;
    int sequenceProgressionModifier;
    int sequenceIndex;
    int time;

    QTimer *timer;

    void createRandomSequence(int sequenceLength);
    void addToSequence(int sequenceLength);

};

#endif // SIMONMODEL_H
