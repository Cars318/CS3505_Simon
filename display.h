#ifndef DISPLAY_H
#define DISPLAY_H
#include "simonmodel.h"
#include "difficulty.h"
#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Display;
}
QT_END_NAMESPACE

class Display : public QMainWindow
{
    Q_OBJECT

public:

    Display(SimonModel& model, QWidget *parent = nullptr);
    ~Display();

public slots:
    void setGameState(int gameState);
    void flashButton(int buttonToFlash, int flashSpeed);
    void setProgressBar(int percentage, bool isCorrect);
    void selectDifficulty(Difficulty difficulty);


private:
    Ui::Display *ui;

};
#endif // DISPLAY_H
