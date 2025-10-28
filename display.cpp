#include "display.h"
#include "ui_display.h"
#include "simonmodel.h"
#include "timer.h"

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

    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::changeButtonColor);

    connect(&model,
            &SimonModel::redButtonState,
            this,
            [this] () {
                ui->redButton->setStyleSheet(QString("QPushButton {background-color: rgb(100,0,0);} "
                                                     "QPushButton:pressed {background-color: rgb(255,0,0);}"));
            });

    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::incrementProgressBar);

    connect(&model,
            &SimonModel::progressBarState,
            this,
            &Display::setProgressBar);

}

Display::~Display()
{
    delete ui;
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
