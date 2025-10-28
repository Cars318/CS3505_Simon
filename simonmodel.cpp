#include "simonmodel.h"
#include <QTimer>
#include <iostream>

SimonModel::SimonModel(QObject *parent)
    : QObject{parent} {
    isRedButtonOn = false;


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

