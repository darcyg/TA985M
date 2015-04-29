#ifndef DCHECKPVD_H
#define DCHECKPVD_H

#include "ui_dcheckpvd.h"


#include <QDebug>
#include <QStateMachine>
#include <QState>
#include <QFinalState>
#include <QMessageBox>

#include <QTimer>

class dCheckPVD : public QDialog, private Ui::dCheckPVD
{
    Q_OBJECT

private:


    QTimer *timer;

    QStateMachine *mashine;

    QState *TopState;           // Верхнее состояние, чтобы организовать выход


    QState *WaitStart;          // Начальное состояние перед стартом
    QState *Start;              // Запуск проверки
    QState *LoadMSS;            // Загрузка иммитаторов МСС

    QFinalState *FinalState;    // Окончание проверки



void CreateStateMashine();


public:
    explicit dCheckPVD(QWidget *parent = 0);


public slots:

    void slotTest1();
    void timeOut();


    void slotStopChecking();
};

#endif // DCHECKPVD_H
