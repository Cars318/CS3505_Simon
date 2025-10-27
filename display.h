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

public:
    Display(SimonModel& model, QWidget *parent = nullptr);
    ~Display();

private:
    Ui::Display *ui;
};
#endif // DISPLAY_H
