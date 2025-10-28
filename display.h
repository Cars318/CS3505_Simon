#ifndef DISPLAY_H
#define DISPLAY_H
#include "simonmodel.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Display;
}
QT_END_NAMESPACE

class Display : public QMainWindow
{
    Q_OBJECT
    enum colors {
        RED,
        BRIGHT_RED,
        BLUE,
        BRIGHT_BLUE
    };

public:

    Display(SimonModel& model, QWidget *parent = nullptr);
    ~Display();

public slots:
    void changeRedButtonColor(colors color);

private:
    Ui::Display *ui;

};
#endif // DISPLAY_H
