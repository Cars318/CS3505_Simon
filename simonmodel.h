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
     * @brief Flashes, or changes the color of the selected button
     *        from dark->light->dark at an inputted flash speed
     * @param buttonToFlash: The selected button to flash
     * @param flashSpeed: The selected speed to perform the flash
     */
    void flashButton(ButtonColor buttonToFlash, int flashSpeed);

    /**
     * @brief Enables and disables specific buttons on screen based
     *        on the state of the game
     * @param stateOfGame: The selected, current state of the game
     */
    void gameState(GameState stateOfGame);

    /**
     * @brief Based on a calculated percentage, sets the progress
     *        bar to that percentage of completion. If isCorrect
     *        is false, the progress bar will be set to 0 and a
     *        "game over" messageBox will appear.
     * @param progressBarPercentage: Numerical value 0-100 to set the bar
     * @param isCorrect: Determines if the sequence is correct or not
     */
    void progressBarState(int progressBarPercentage, bool isCorrect);

    /**
     * @brief Changes the button colors of the Easy, Medium, and
     *        Hard buttons based on the selected difficulty. The
     *        selected button will be highlighted, while the other
     *        two will be grayed out
     * @param difficulty: The selected, current difficulty mode
     */
    void difficultySelected(Difficulty difficulty);

public slots:
    /**
     * @brief Handles the timeout and flash of the current index
     *        of the sequence, and emits a signal to flash the
     *        colored button corresponding to that index.
     *        Increments the sequence index in preparation for
     *        the next flash.
     */
    void handleFlash();

    /**
     * @brief Provides setup for the start of a game and
     *        kicks off the start of the game.
     *        Calls to create a random sequence, then
     *        signals the game state to be the computer's
     *        flashing sequence, and finally calls to
     *        handle the flashing.
     */
    void startGame();

    /**
     * @brief Provides a confirmation that the red button
     *        has been clicked, then calls to increment the
     *        progress bar based on that confirmation
     */
    void noteRedButtonClick();

    /**
     * @brief Provides a confirmation that the blue button
     *        has been clicked, then calls to increment the
     *        progress bar based on that confirmation
     */
    void noteBlueButtonClick();

    /**
     * @brief Resets the game mode values to easy,
     *        then signals for the Easy Button to
     *        be selected and colored
     */
    void setEasy();

    /**
     * @brief Resets the game mode values to medium,
     *        then signals for the Medium Button to
     *        be selected and colored
     */
    void setMedium();

    /**
     * @brief Resets the game mode values to hard,
     *        then signals for the Hard Button to
     *        be selected and colored
     */
    void setHard();

    /**
     * @brief Determines if the correct button was pressed,
     *        and performs the calculations necessary to
     *        increment the progress bar based on the
     *        amounted completion in the sequence.
     *        At the end of a sequence, the progress bar will
     *        be reset and the game state will be signaled
     *        to be the computer's turn.
     */
    void incrementProgressBar();

private:
    QVector<ButtonColor> sequenceList;
    QTimer timer;

    bool isGameRunning;
    bool redButtonClicked;
    bool blueButtonClicked;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceIndex;
    int currentInputIndex;

    // Describes the conditions of each mode or difficulty
    struct {
        int flashSpeed;
        int pauseDuration;
        int sequenceLength;
        int progressModifier;
        double speedupModifier;
    } easyMode, mediumMode, hardMode, initMode, curMode;

    // Helper Methods
    /**
     * @brief Based on the current selected difficulty,
     *        performs simple calculations to determine
     *        the speed of the flash and duration of pause
     *        between flashes in the current sequence.
     */
    void calculateFlashSpeed();

    /**
     * @brief Creats a list of a random sequence using
     *        the number of colors and length based on
     *        the current difficulty.
     */
    void createRandomSequence();

    /**
     * @brief Appends the sequence list by a number equal
     *        to a modifier from the current selected
     *        difficulty.
     */
    void addToSequence();

    /**
     * @brief Resets all necessary variables to the
     *        initial state, and set the color sequence
     *        to be empty.
     */
    void resetGame();

    /**
     * @brief Calls to append the sequence, sets the
     *        ncessary variables for the start of a
     *        new sequence, then kicks off to continue
     *        the game.
     */
    void nextSequence();
};

#endif // SIMONMODEL_H
