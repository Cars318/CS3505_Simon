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
    /**
     * @brief flashButton
     * @param buttonToFlash
     * @param flashSpeed
     */
    void flashButton(ButtonColor buttonToFlash, int flashSpeed);

    /**
     * @brief gameState
     * @param stateOfGame
     */
    void gameState(GameState stateOfGame);

    /**
     * @brief progressBarState
     * @param progressBarPercentage
     * @param isCorrect
     */
    void progressBarState(int progressBarPercentage, bool isCorrect);

    /**
     * @brief startButtonState
     * @param isStartButtonActive
     */
    void startButtonState(bool isStartButtonActive);

    /**
     * @brief difficultySelected
     * @param difficulty
     */
    void difficultySelected(Difficulty difficulty);

public slots:
    /**
     * @brief handleFlash
     */
    void handleFlash();

    /**
     * @brief startGame
     */
    void startGame();

    /**
     * @brief incrementProgressBar
     */
    void incrementProgressBar();

    /**
     * @brief noteRedButtonClick
     */
    void noteRedButtonClick();

    /**
     * @brief noteBlueButtonClick
     */
    void noteBlueButtonClick();

    /**
     * @brief setEasy
     */
    void setEasy();

    /**
     * @brief setMedium
     */
    void setMedium();

    /**
     * @brief setHard
     */
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
    /**
     * @brief calculateFlashSpeed
     */
    void calculateFlashSpeed();

    /**
     * @brief createRandomSequence
     */
    void createRandomSequence();

    /**
     * @brief addToSequence
     */
    void addToSequence();

    /**
     * @brief resetGame
     */
    void resetGame();

    /**
     * @brief nextSequence
     */
    void nextSequence();
};

#endif // SIMONMODEL_H
