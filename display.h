#ifndef DISPLAY_H
#define DISPLAY_H
#include "simonmodel.h"
#include "buttoncolor.h"
#include "difficulty.h"
#include "gamestate.h"

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
    /**
     * @brief setGameState
     * @param gameState
     */
    void setGameState(GameState gameState);

    /**
     * @brief flashButton
     * @param buttonToFlash
     * @param flashSpeed
     */
    void flashButton(ButtonColor buttonToFlash, int flashSpeed);

    /**
     * @brief setProgressBar
     * @param percentage
     * @param isCorrect
     */
    void setProgressBar(int percentage, bool isCorrect);

    /**
     * @brief selectDifficulty
     * @param difficulty
     */
    void selectDifficulty(Difficulty difficulty);


private:
    Ui::Display *ui;

};
#endif // DISPLAY_H
