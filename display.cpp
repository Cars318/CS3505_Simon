#include "display.h"
#include "ui_display.h"
#include "simonmodel.h"
#include <QVector>
#include <QTimer>
#include <iostream>

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
    ui->blueButton->setEnabled(false);
    setGameState(0);

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
            this,
            [this] () {
                ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,0,0);}"));
                QTimer::singleShot(100, this, [this] () {
                    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}"));
                });
            });

    connect(ui->blueButton,
            &QPushButton::clicked,
            this,
            [this] () {
                ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,255);}"));
                                              QTimer::singleShot(100, this, [this] () {
                                                    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}"));
                });
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
            &SimonModel::flashButton,
            this,
            &Display::flashButton);

}

Display::~Display()
{
    delete ui;
}

void Display::setGameState(int gameState) {
    switch(gameState) {
    case 0: // State 0 = Initial; Red/Blue Disabled, Start Enabled
        std::cout << "Initial" << std::endl;
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        ui->startButton->setEnabled(true);
        break;
    case 1: // State 1 = Game Turn; Red/Blue/Start Disabled
        std::cout << "Computer" << std::endl;
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        ui->startButton->setEnabled(false);
        break;
    case 2: // State 2 = Player Turn; Start Disabled, Red/Blue Enabled
        std::cout << "Player" << std::endl;
        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        ui->startButton->setEnabled(false);
        break;
    }
}

void Display::flashButton(int buttonToFlash, int flashSpeed) {
    if (buttonToFlash == 0) { // Red Button
            ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}"));
        QTimer::singleShot(flashSpeed, this,[this]() {
            ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,0,0);}"));
        });
        QTimer::singleShot(flashSpeed*5, this,[this]() {
            ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}"));
        });
    } else {
        ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}"));
        QTimer::singleShot(flashSpeed, this,[this]() {
            ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,255);}"));
        });
        QTimer::singleShot(flashSpeed*5, this,[this]() {
            ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}"));
        });
    }
}

void Display::setProgressBar(int percentage) {
    ui->progressBar->setValue(percentage);

}
