#include "simonmodel.h"
#include "buttoncolor.h"
#include "difficulty.h"
#include "gamestate.h"
#include <QTimer>
#include <QVector>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    // Initialize Variables
    sequenceList = {};
    isStartButtonActive = true;
    isGameRunning = false;
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    numberOfColors = 2;
    sequenceIndex = 0;
    currentInputIndex = 0;

    // Initialize Difficulty Values
    easyMode.flashSpeed = 200;
    easyMode.pauseDuration = 1000;
    easyMode.sequenceLength = 1;
    easyMode.progressModifier = 1;
    easyMode.speedupModifier = 1.25;

    mediumMode.flashSpeed = 150;
    mediumMode.pauseDuration = 750;
    mediumMode.sequenceLength = 2;
    mediumMode.progressModifier = 2;
    mediumMode.speedupModifier = 1.5;

    hardMode.flashSpeed = 100;
    hardMode.pauseDuration = 500;
    hardMode.sequenceLength = 3;
    hardMode.progressModifier = 3;
    hardMode.speedupModifier = 1.75;

    initMode = easyMode;
    curMode = easyMode;

    timer.setInterval(curMode.pauseDuration);

    connect(&timer,
            &QTimer::timeout,
            this,
            &SimonModel::handleTimeout);
}

// ========== Helper Methods  ==========

// Helper Method to Create a random sequence
void SimonModel::createRandomSequence() {
    for (int i = 0; i < curMode.sequenceLength; i++) {
        sequenceList.append((ButtonColor)(rand() % numberOfColors));
    }

}

// Helper method to add randomly to the end of a sequence
void SimonModel::addToSequence() {
    for (int i = 0; i < curMode.progressModifier; i++) {
         sequenceList.append((ButtonColor)(rand() % numberOfColors));
    }
}

// Resets all Variables to Initial Values
void SimonModel::resetGame() {
    sequenceList = {};
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    sequenceIndex = 0;
    currentInputIndex = 0;
    curMode = initMode;
}

// Sets up the Game for the next, longer sequence
void SimonModel::nextSequence() {
    addToSequence();
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    sequenceIndex = 0;
    currentInputIndex = 0;
    curMode.sequenceLength += curMode.progressModifier;
    calculateFlashSpeed();
    handleTimeout();
}

void SimonModel::calculateFlashSpeed() {
    curMode.flashSpeed = curMode.flashSpeed/curMode.speedupModifier;
    curMode.pauseDuration = curMode.pauseDuration/curMode.speedupModifier;
}

// ========== Slots  ==========


void SimonModel::handleTimeout() {
    if (sequenceIndex >= curMode.sequenceLength) {
        emit gameState(GameState::Player);
        return;
    }
    emit flashButton(sequenceList.at(sequenceIndex), curMode.flashSpeed);
    timer.start(curMode.pauseDuration);
    sequenceIndex++;
}

// Starts the game and sets the states
void SimonModel::startGame() {
    emit gameState(GameState::Computer);
    emit startButtonState(false);
    isGameRunning = true;
    isStartButtonActive = false;
    createRandomSequence();
    timer.setSingleShot(true);
    handleTimeout();
}

// Set the game to
void SimonModel::setEasy() {
    initMode = easyMode;
    resetGame();
    emit difficultySelected(Difficulty::Easy);
}

void SimonModel::setMedium() {
    initMode = mediumMode;
    resetGame();
    emit difficultySelected(Difficulty::Medium);
}

void SimonModel::setHard() {
     initMode = hardMode;
    resetGame();
    emit difficultySelected(Difficulty::Hard);
}

void SimonModel::noteRedButtonClick() {
    redButtonClicked = true;
    incrementProgressBar();
}

void SimonModel::noteBlueButtonClick() {
    blueButtonClicked = true;
    incrementProgressBar();
}

// Proportionally increments the progress bar
void SimonModel::incrementProgressBar() {
    // Correct Button Pressed
    if ((redButtonClicked && (sequenceList.at(currentInputIndex) == ButtonColor::Red)) ||
        (blueButtonClicked && (sequenceList.at(currentInputIndex) == ButtonColor::Blue))) {
        currentInputIndex++;

        // For last turn in sequence, assure progress bar achieves 100%,
        // even if the math would put it at something like 98%
        if (currentInputIndex == sequenceList.length()) {
            progressBarPercentage = 100;
        } else {
            progressBarPercentage += (100 / curMode.sequenceLength);
        }
        emit progressBarState(progressBarPercentage, true);
        redButtonClicked = false;
        blueButtonClicked = false;

        // End of Sequence, change game State and reset progress bar
        if (currentInputIndex == curMode.sequenceLength) {
             emit gameState(GameState::Computer); //Computer's next turn
            QTimer::singleShot(1500, this, [this]() {
                 emit progressBarState(0, true); });
            QTimer::singleShot(1500, this, [this]() {
                 nextSequence(); });
        }
    // Incorrect Button Pressed
    } else {
        resetGame();
        emit progressBarState(progressBarPercentage, false);
        emit gameState(GameState::Initial);
    }
}





