#include "simonmodel.h"
#include <QTimer>
#include <QVector>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    sequenceList = {};
    currentFlashState = 0;
    isStartButtonActive = true;
    isGameRunning = false;
    isRedButtonOn = false;
    progressBarPercentage = 0;
    numberOfColors = 2;
    sequenceLength = 5;
    sequenceProgressionModifier = 2;
    sequenceIndex = 0;
    flashTime = 100;
    time = 0;
    timer.setInterval(1000);

    connect(&timer,
            &QTimer::timeout,
            this,
            &SimonModel::handleTimeout);
}


void SimonModel::handleTimeout() {
    if (sequenceIndex >= sequenceLength) {
        return;
    }
        int buttonToFlash = sequenceList.at(sequenceIndex);
        emit flashButton(buttonToFlash);
        timer.start(1000);
        sequenceIndex++;
        std::cout << sequenceIndex << std::endl;
}

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

// Starts the game and sets the states
void SimonModel::startGame() {
    emit gameState(true);
    emit startButtonState(false);
    isGameRunning = true;
    isStartButtonActive = false;
    createRandomSequence(sequenceLength);

    timer.setSingleShot(true);


    handleTimeout();
}

void SimonModel::changeButtonColor() {
    if (isRedButtonOn) {
        emit redButtonState(true);
    }
    else {
        emit redButtonState(false);
    }
    isRedButtonOn = !isRedButtonOn;
}

// Proportionally increments the progress bar
void SimonModel::incrementProgressBar() {
    progressBarPercentage += (100 / sequenceLength);
    emit progressBarState(progressBarPercentage);
}





