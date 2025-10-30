#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include "buttoncolor.h"
#include "difficulty.h"
#include "gamestate.h"
#include <QWidget>
#include <QTimer>
#include <QVector>

class SimonModel : public QObject
{
    Q_OBJECT
public:
    explicit SimonModel(QObject *parent = nullptr);

signals:
    void flashButton(ButtonColor buttonToFlash, int flashSpeed);
    void gameState(GameState stateOfGame);
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
    QVector<ButtonColor> sequenceList;
    QTimer timer;

    bool isGameRunning;
    bool isStartButtonActive;
    bool redButtonClicked;
    bool blueButtonClicked;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceIndex;
    int currentInputIndex;

    struct {
        int flashSpeed;
        int pauseDuration;
        int sequenceLength;
        int progressModifier;
        double speedupModifier;
    } easyMode, mediumMode, hardMode, initMode, curMode;

    // Helper Methods
    void calculateFlashSpeed();
    void createRandomSequence();
    void addToSequence();
    void resetGame();
    void nextSequence();
};

#endif // SIMONMODEL_H
