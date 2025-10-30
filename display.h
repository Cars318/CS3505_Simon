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
     * @brief Enables and disables specific buttons on screen based
     *        on the state of the game
     * @param gameState: The selected, current state of the game
     */
    void setGameState(GameState gameState);

    /**
     * @brief Changes the button colors of the Easy, Medium, and
     *        Hard buttons based on the selected difficulty. The
     *        selected button will be highlighted, while the other
     *        two will be grayed out
     * @param difficulty: The selected, current difficulty mode
     */
    void selectDifficulty(Difficulty difficulty);

    /**
     * @brief Flashes, or changes the color of the selected button
     *        from dark->light->dark at an inputted flash speed
     * @param buttonToFlash: The selected button to flash
     * @param flashSpeed: The selected speed to perform the flash
     */
    void flashButton(ButtonColor buttonToFlash, int flashSpeed);

    /**
     * @brief Based on a calculated percentage, sets the progress
     *        bar to that percentage of completion. If isCorrect
     *        is false, the progress bar will be set to 0 and a
     *        "game over" messageBox will appear.
     * @param percentage: Numerical value 0-100 to set the bar
     * @param isCorrect: Determines if the sequence is correct or not
     */
    void setProgressBar(int percentage, bool isCorrect);




private:
    Ui::Display *ui;

};
#endif // DISPLAY_H
