#include "simonmodel.h"
#include <QTimer>
#include <QVector>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    sequenceList = {};
    isFlashing = false;
    isStartButtonActive = true;
    isGameRunning = false;
    isRedButtonOn = false;
    progressBarPercentage = 0;
    numberOfColors = 2;
    sequenceLength = 10;
    sequenceProgressionModifier = 2;
    sequenceIndex = 0;
    time = 0;
    timer->setInterval(1000);
/*
    connect(timer,
            &QTimer::timeout,
            this,
            &SimonModel::handleTimeout);
*/
}


void SimonModel::handleTimeout() {
    isFlashing = !isFlashing;

    int buttonToFlash = sequenceList.at(sequenceIndex);

    emit flashingStateChanged(buttonToFlash, isFlashing);

    if (!isFlashing) {
        sequenceIndex++;
        if (sequenceIndex < sequenceLength) {
            timer->stop();
        }
    }
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

    timer->start();
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





