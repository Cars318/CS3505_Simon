#include "simonmodel.h"
#include <QTimer>
#include <QVector>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    sequenceList = {};
    isStartButtonActive = true;
    isGameRunning = false;
    isRedButtonOn = false;
    progressBarPercentage = 0;
    numberOfColors = 2;
    sequenceLength = 10;
    sequenceProgressionModifier = 2;
    time = 0;


}

// Helper Method to Create a random sequence
void SimonModel::createRandomSequence(int sequenceLength) {
    for (int i = 0; i < sequenceLength; i++) {
        sequenceList.push_back(rand() % numberOfColors);
        //sequenceList.push_back(0);
    }
}

// Helper method to add randomly to the end of a sequence
void SimonModel::addToSequence(int sequenceProgressionModifier) {
    for (int i = 0; i < sequenceProgressionModifier; i++) {
         sequenceList.push_back(rand() % numberOfColors);
    }
}

// Starts the game and sets the states
void SimonModel::startGame() {
    emit gameState(true);
    emit startButtonState(false);
    isGameRunning = true;
    isStartButtonActive = false;
    createRandomSequence(sequenceLength);
    timer.start();
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





