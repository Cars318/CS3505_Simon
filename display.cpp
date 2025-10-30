#include "display.h"
#include "ui_display.h"
#include "simonmodel.h"
#include "buttoncolor.h"
#include "difficulty.h"
#include "gamestate.h"
#include <QVector>
#include <QTimer>
#include <QObject>

Display::Display(SimonModel& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Display)
{
    ui->setupUi(this);
    setGameState(GameState::Initial);

    // Set up Colored Buttons
    ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}"));
    ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}"));

    // Set up Progress Bar
    ui->progressBar->setOrientation(Qt::Horizontal);
    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    // Set up Difficulty Buttons
    ui->easyButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,255,0);}"));
    ui->mediumButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
    ui->hardButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));

    // Set the Game State Using the Start Button
    connect(ui->startButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::startGame);

    connect(&model,
            &SimonModel::gameState,
            this,
            &Display::setGameState);

    // Flash the Buttons in the Order of the Sequence
    connect(&model,
            &SimonModel::flashButton,
            this,
            &Display::flashButton);


    // Flash the Button as Visual Confirmation of Click
    connect(ui->redButton,
            &QPushButton::clicked,
            this,
            [this] () {
                ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,0,0);}"));
                                             QTimer::singleShot(200, this, [this] () {
                ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(150,0,0);}"));
                });
            });

    connect(ui->blueButton,
            &QPushButton::clicked,
            this,
            [this] () {
                ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,255);}"));
                                              QTimer::singleShot(200, this, [this] () {
                ui->blueButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,0,150);}"));
                });
            });

    // Change Game Mode Difficulty When Button is Clicked
    connect(ui->easyButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::setEasy);

    connect(ui->mediumButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::setMedium);

    connect(ui->hardButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::setHard);

    connect(&model,
            &SimonModel::difficultySelected,
            this,
            &Display::selectDifficulty);


    // Increment the Progress Bar when the Buttons are Clicked
    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::noteRedButtonClick);

    connect(ui->blueButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::noteBlueButtonClick);

    connect(&model,
            &SimonModel::progressBarState,
            this,
            &Display::setProgressBar);
}

Display::~Display()
{
    delete ui;
}

// Enables and Disables buttons on-screen based on the inputted game state
void Display::setGameState(GameState gameState) {
    switch(gameState) {
    case (GameState::Initial):
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        ui->startButton->setEnabled(true);

        ui->easyButton->setEnabled(true);
        ui->mediumButton->setEnabled(true);
        ui->hardButton->setEnabled(true);
        break;
    case (GameState::Computer):
        ui->redButton->setEnabled(false);
        ui->blueButton->setEnabled(false);
        ui->startButton->setEnabled(false);

        ui->easyButton->setEnabled(false);
        ui->mediumButton->setEnabled(false);
        ui->hardButton->setEnabled(false);
        break;
    case (GameState::Player):
        ui->redButton->setEnabled(true);
        ui->blueButton->setEnabled(true);
        ui->startButton->setEnabled(false);

        ui->easyButton->setEnabled(false);
        ui->mediumButton->setEnabled(false);
        ui->hardButton->setEnabled(false);
        break;
    }
}

// Changes the Easy, Medium, and Hard difficulty buttons based on the selected difficulty
void Display::selectDifficulty(Difficulty difficulty) {
    switch (difficulty) {
    case (Difficulty::Easy): // Easy
        ui->easyButton->setStyleSheet(QString("QPushButton {background-color: rgb(0,255,0);}"));
        ui->mediumButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        ui->hardButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        break;
    case (Difficulty::Medium): // Medium
        ui->easyButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        ui->mediumButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,150,0);}"));
        ui->hardButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        break;
    case (Difficulty::Hard): // Hard
        ui->easyButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        ui->mediumButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,100,100);}"));
        ui->hardButton->setStyleSheet(QString("QPushButton {background-color: rgb(255,0,0);}"));
        break;
    }
}

// Flashes, or changes the color of the selected button from dark->light->dark at a selected flash speed
void Display::flashButton(ButtonColor buttonToFlash, int flashSpeed) {
    if (buttonToFlash == ButtonColor::Red) {
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

// Changes the value on the progress bar to the input percentage
// Will display a "game over" box if the input sequence was incorrect
void Display::setProgressBar(int percentage, bool isCorrect) {
    if (isCorrect) {
        ui->progressBar->setValue(percentage);
    }
    else {
        QMessageBox messageBox;
        messageBox.setWindowTitle("Game Over!");
        messageBox.setText("You Lost! Nice Try Though!");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setStandardButtons(QMessageBox::Reset);
        messageBox.exec();
        ui->progressBar->setValue(0);
    }
}
