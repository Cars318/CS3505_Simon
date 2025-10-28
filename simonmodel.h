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
    enum FlashingState {
        FLASH_ON,
        FLASH_OFF,
        FLASH_PAUSE
    };

signals:
    void flashRed();
    void flashBlue();
    void flashButton(int buttonToFlash);
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
    bool isGameRunning;
    bool isStartButtonActive;
    bool isRedButtonOn;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceLength;
    int sequenceProgressionModifier;
    int sequenceIndex;
    int flashTime;
    int time;

    QTimer timer;



    int currentFlashState;

    void createRandomSequence(int sequenceLength);
    void addToSequence(int sequenceLength);

};

#endif // SIMONMODEL_H
