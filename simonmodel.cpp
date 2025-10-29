#include "simonmodel.h"
#include "difficulty.h"
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
    mediumMode.sequenceLength = 3;
    mediumMode.progressModifier = 2;
    mediumMode.speedupModifier = 1.5;

    hardMode.flashSpeed = 100;
    hardMode.pauseDuration = 500;
    hardMode.sequenceLength = 4;
    hardMode.progressModifier = 3;
    hardMode.speedupModifier = 1.75;

    flashSpeed = easyMode.flashSpeed;
    pauseDuration = easyMode.pauseDuration;
    sequenceLength = easyMode.sequenceLength;
    sequenceProgressionModifier = easyMode.progressModifier;
    speedupModifier = easyMode.speedupModifier;

    initialFlashSpeed = easyMode.flashSpeed;
    initialPauseDuration = easyMode.pauseDuration;
    initialSequenceLength = easyMode.sequenceLength;
    initialSequenceProgressModifier = easyMode.progressModifier;
    initialSpeedupModifier = easyMode.speedupModifier;

    timer.setInterval(pauseDuration);

    connect(&timer,
            &QTimer::timeout,
            this,
            &SimonModel::handleTimeout);
}

// ========== Helper Methods  ==========

// Helper Method to Create a random sequence
void SimonModel::createRandomSequence(int sequenceLength) {
    for (int i = 0; i < sequenceLength; i++) {
        sequenceList.append(rand() % numberOfColors);
        //sequenceList.push_back(0);
    }
}

// Helper method to add randomly to the end of a sequence
void SimonModel::addToSequence(int sequenceProgressionModifier) {
    for (int i = 0; i < sequenceProgressionModifier; i++) {
         sequenceList.append(rand() % numberOfColors);
    }
}

// Resets the State of the Game and all Variables to Default
void SimonModel::resetGame() {
    sequenceList = {};
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    sequenceIndex = 0;
    currentInputIndex = 0;

    flashSpeed = initialFlashSpeed;
    pauseDuration = initialPauseDuration;
    sequenceLength = initialSequenceLength;
    sequenceProgressionModifier = initialSequenceProgressModifier;
    speedupModifier = initialSpeedupModifier;

}

// Sets up the Game for the next, longer sequence
void SimonModel::nextSequence() {
    addToSequence(sequenceProgressionModifier);
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    sequenceIndex = 0;
    currentInputIndex = 0;
    sequenceLength += sequenceProgressionModifier;
    calculateFlashSpeed();
    handleTimeout();
}

void SimonModel::calculateFlashSpeed() {
    flashSpeed = flashSpeed/speedupModifier;
    pauseDuration = pauseDuration/speedupModifier;
}

// ========== Slots  ==========

void SimonModel::handleTimeout() {
    if (sequenceIndex >= sequenceLength) {
        emit gameState(2);
        return;
    }
    int buttonToFlash = sequenceList.at(sequenceIndex);
    emit flashButton(buttonToFlash, flashSpeed);
    timer.start(pauseDuration);
    sequenceIndex++;
}

// Starts the game and sets the states
void SimonModel::startGame() {
    emit gameState(1);
    emit startButtonState(false);
    isGameRunning = true;
    isStartButtonActive = false;
    createRandomSequence(sequenceLength);
    timer.setSingleShot(true);
    handleTimeout();
}

void SimonModel::setEasy() {
    initialFlashSpeed = easyMode.flashSpeed;
    initialPauseDuration = easyMode.pauseDuration;
    initialSequenceLength = easyMode.sequenceLength;
    initialSequenceProgressModifier = easyMode.progressModifier;
    initialSpeedupModifier = easyMode.speedupModifier;
    resetGame();
    emit difficultySelected(Difficulty::Easy);
}

void SimonModel::setMedium() {
    initialFlashSpeed = mediumMode.flashSpeed;
    initialPauseDuration = mediumMode.pauseDuration;
    initialSequenceLength = mediumMode.sequenceLength;
    initialSequenceProgressModifier = mediumMode.progressModifier;
    initialSpeedupModifier = mediumMode.speedupModifier;
    resetGame();
    emit difficultySelected(Difficulty::Medium);
}

void SimonModel::setHard() {
    initialFlashSpeed = hardMode.flashSpeed;
    initialPauseDuration = hardMode.pauseDuration;
    initialSequenceLength = hardMode.sequenceLength;
    initialSequenceProgressModifier = hardMode.progressModifier;
    initialSpeedupModifier = hardMode.speedupModifier;
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
    if ((redButtonClicked && (sequenceList.at(currentInputIndex) == 0)) ||
        (blueButtonClicked && (sequenceList.at(currentInputIndex) == 1))) {
        currentInputIndex++;
        if (currentInputIndex == sequenceList.length()) {
            progressBarPercentage = 100;
        } else {
            progressBarPercentage += (100 / sequenceLength);
        }
        emit progressBarState(progressBarPercentage, true);
        redButtonClicked = false;
        blueButtonClicked = false;
        if (currentInputIndex == sequenceLength) {
             emit gameState(1); //Computer's next turn
            QTimer::singleShot(1500, this, [this]() {
                 emit progressBarState(0, true); });
            QTimer::singleShot(1500, this, [this]() {
                 nextSequence(); });
        }
    } else {
        resetGame();
        emit progressBarState(progressBarPercentage, false);
        emit gameState(0);
    }
}





