#include "simonmodel.h"
#include <QTimer>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {

    isGameRunning = false;
    isRedButtonOn = false;
    progressBarPercentage = 0;
    sequenceLength = 10;



}

void SimonModel::changeGameState() {
    if (isGameRunning) {
        emit gameState(false);
    }
    else {
        emit gameState(false);
    }
}

void SimonModel::changeButtonColor() {
    if (!isRedButtonOn) {
        std::cout << "Activate Red Button" << std::endl;
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





