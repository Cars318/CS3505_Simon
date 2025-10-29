#ifndef SIMONMODEL_H
#define SIMONMODEL_H

#include <QWidget>
#include <QTimer>
#include <QVector>

class SimonModel : public QObject
{
    Q_OBJECT
public:
    explicit SimonModel(QObject *parent = nullptr);

signals:
    void flashButton(int buttonToFlash, int flashSpeed);
    void gameState(int stateOfGame);
    void progressBarState(int progressBarPercentage, bool isCorrect);
    void startButtonState(bool isStartButtonActive);

public slots:
    void handleTimeout();
    void startGame();
    void incrementProgressBar();
    void noteRedButtonClick();
    void noteBlueButtonClick();

private:
    QVector<int> sequenceList;
    QTimer timer;

    bool isGameRunning;
    bool isStartButtonActive;
    bool redButtonClicked;
    bool blueButtonClicked;

    int progressBarPercentage;
    int numberOfColors;
    int sequenceLength;
    int sequenceProgressionModifier;
    int sequenceIndex;
    int flashSpeed;
    int currentInputIndex;

    // Helper Methods
    int calculateFlashSpeed(int initialSpeed);
    void createRandomSequence(int sequenceLength);
    void addToSequence(int sequenceLength);


};

#endif // SIMONMODEL_H
