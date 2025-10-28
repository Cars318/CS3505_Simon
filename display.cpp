#include "display.h"
#include "ui_display.h"
#include "simonmodel.h"
#include "timer.h"

Display::Display(SimonModel& model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Display)
{
    ui->setupUi(this);

    connect(ui->redButton,
            &QPushButton::clicked,
            &model,
            &SimonModel::changeButtonColor);

    connect(&model,
            &SimonModel::redButtonState,
            this,
            [this] (bool isRedButtonOn) {
                ui->redButton->setStyleSheet( isRedButtonOn ? QString("QPushButton {background-color: rgb(100,0,0);} "
                                                     "QPushButton:pressed {background-color: rgb(255,150,150);}"):
                                                    QString("QPushButton {background-color: rgb(255,0,0);} "
                                                     "QPushButton:pressed {background-color: rgb(255,150,150);}"));
            });
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
