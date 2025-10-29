#include "simonmodel.h"
#include <QTimer>
#include <QVector>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    sequenceList = {};
    isStartButtonActive = true;
    isGameRunning = false;
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    numberOfColors = 2;
    sequenceLength = 3;
    sequenceProgressionModifier = 2;
    sequenceIndex = 0;
    currentInputIndex = 0;
    flashSpeed = 200;
    timer.setInterval(1000);

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
    std::cout << sequenceList.length() << std::endl;
}

// Resets the State of the Game and all Variables to Default
void SimonModel::resetGame() {
    sequenceList = {};
    isStartButtonActive = true;
    isGameRunning = false;
    redButtonClicked = false;
    blueButtonClicked = false;
    progressBarPercentage = 0;
    sequenceIndex = 0;
    currentInputIndex = 0;
    sequenceLength = 3;
    sequenceProgressionModifier = 2;
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
    handleTimeout();
}


// ========== Slots  ==========

void SimonModel::handleTimeout() {
    //std::cout << "Index: " << sequenceIndex << std::endl;
    std::cout << "Length: " << sequenceLength << std::endl;
    if (sequenceIndex >= sequenceLength) {
        emit gameState(2);
        return;
    }
    int buttonToFlash = sequenceList.at(sequenceIndex);
    emit flashButton(buttonToFlash, flashSpeed);
    timer.start(1000);
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
        std::cout << "Wrong Color" << std::endl;
        resetGame();
        emit progressBarState(progressBarPercentage, false);
        emit gameState(0);
    }
}





