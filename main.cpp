/*
 * Name: Carson Ord
 * GitHub Username: Cars318
 *
 * Description of Unique Game Element:
 * The game element added to the Simon Game is an option for
 * the player to choose between easy, medium, or hard difficulty.
 * The difficulty can be selected by pressing a button, which
 * grays out the other two options, clearly indicating which
 * difficulty the player is currently on.
 *
 * Changing the difficulty changes these conditions:
 *  - Number in starting color sequence
 *  - Number added to Each subsequent color sequence
 *  - Speed of flashes in each color sequence
 *  - Pause between flashes in each color sequence
 *  - Amount by which speedup occurs in each subsequence sequence
*/


#include "display.h"
#include "simonmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimonModel simon;
    Display w(simon);
    w.show();
    return a.exec();
}
