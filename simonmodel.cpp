#include "simonmodel.h"
#include <QTimer>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    isStartButtonActive = true;
    isGameRunning = false;
    isRedButtonOn = false;
    progressBarPercentage = 0;
    sequenceLength = 10;


}

void SimonModel::startGame() {
    emit gameState(true);
    emit startButtonState(false);
    isGameRunning = true;
    isStartButtonActive = false;
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

void SimonModel::incrementProgressBar() {
    progressBarPercentage += (100 / sequenceLength);
    emit progressBarState(progressBarPercentage);
}





