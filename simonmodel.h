#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include "difficulty.h"
#include <QWidget>
#include <QTimer>
#include <QVector>

class SimonModel : public QObject
{
    Q_OBJECT
public:
    explicit SimonModel(QObject *parent = nullptr);

signals:
    void flashButton(int buttonToFlash, int flashSpeed);
    void gameState(int stateOfGame);
    void progressBarState(int progressBarPercentage, bool isCorrect);
    void startButtonState(bool isStartButtonActive);
    void difficultySelected(Difficulty difficulty);

public slots:
    void handleTimeout();
    void startGame();
    void incrementProgressBar();
    void noteRedButtonClick();
    void noteBlueButtonClick();

    void setEasy();
    void setMedium();
    void setHard();

private:
    QVector<int> sequenceList;
    QTimer timer;

    bool isGameRunning;
    bool isStartButtonActive;
    bool redButtonClicked;
    bool blueButtonClicked;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceLength;
    int sequenceProgressionModifier;
    int sequenceIndex;
    int flashSpeed;
    int pauseDuration;
    int currentInputIndex;

    double speedupModifier;

    int initialFlashSpeed;
    int initialPauseDuration;
    int initialSequenceLength;
    int initialSequenceProgressModifier;
    int initialSpeedupModifier;

    struct {
        int flashSpeed;
        int pauseDuration;
        int sequenceLength;
        int progressModifier;
        double speedupModifier;
    } easyMode, mediumMode, hardMode;

    // Helper Methods
    void calculateFlashSpeed();
    void createRandomSequence(int sequenceLength);
    void addToSequence(int sequenceLength);
    void resetGame();
    void nextSequence();
};

#endif // SIMONMODEL_H
