#include "display.h"
#include "ui_display.h"
#include "simonmodel.h"
#include <QVector>
#include <QTimer>

Display::Display(SimonModel& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Display)
{
    ui->setupUi(this);

    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(150,0,0);}"));
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,0,150);}"));
    ui->progressBar->setOrientation(Qt::Horizontal);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);
    ui->redButton->setEnabled(false);

    // Set the Game State Using the Start Button
    connect(ui->startButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::startGame);

    connect(&model,
            &SimonModel::gameState,
            this,
            &Display::setGameState);

    // Change the Button Colors
    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::changeButtonColor);

    connect(&model,
            &SimonModel::redButtonState,
            this,
            [this] () {
                ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);} "
                                                     "QPushButton:pressed {background-color: rgb(255,0,0);}"));
            });

    // Increment the Progress Bar when the Buttons are Clicked
    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::incrementProgressBar);

    connect(ui->blueButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::incrementProgressBar);

    connect(&model,
            &SimonModel::progressBarState,
            this,
            &Display::setProgressBar);

    // Flash the Buttons in the Order of the Sequence
    connect(&model,
            &SimonModel::flashingStateChanged,
            this,
            &Display::flashButton);

}

Display::~Display()
{
    delete ui;
}

void Display::setGameState(bool gameState) {
    ui->redButton->setEnabled(gameState);
    ui->blueButton->setEnabled(gameState);
    ui->startButton->setEnabled(!gameState);
}

void Display::flashButton(int buttonToFlash, bool isFlashing) {
    if (buttonToFlash == 0) {
        if (!isFlashing) {
            ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,0,0);}" ));
        } else {
             ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}" ));
        }
    } else {
        if (!isFlashing) {
            ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}" ));
        } else {
            ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,255);}" ));
        }
    }
}


void Display::changeRedButtonColor(colors color) {
    if (color == RED) {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(150,0,0);} "
                                             "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    } else if(color == BRIGHT_RED) {
        ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(255,50,50);} "
                                             "QPushButton:pressed {background-color: rgb(255,150,150);}"));
    }

}

void Display::setProgressBar(int percentage) {
    ui->progressBar->setValue(percentage);

}
