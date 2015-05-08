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


    Q_PROPERTY(quint8 currBD_Number READ currBDNum WRITE setCurrBD_Number)
    Q_PROPERTY(bool  LoadMSS READ LoadMSS WRITE setLoadMSS )

    QTimer *timer;

    QStateMachine *mashine;

    QState *TopState;           // Верхнее состояние, чтобы организовать выход


    QState *sWaitStart;          // Начальное состояние перед стартом
    QState *sStart;              // Запуск проверки
    QState *sLoadMSS;            // Загрузка иммитаторов МСС

    QFinalState *FinalState;    // Окончание проверки

    quint8 m_currBDNum;         // Текущий проверяемы БД
    bool m_LoadMSS;             // Флаг загрузки имитатора МСС


    void CreateStateMashine();

    quint8 currBDNum() {return m_currBDNum;}
    bool LoadMSS() {return m_LoadMSS;}




public:
    explicit dCheckPVD(QWidget *parent = 0);


public slots:

    void slotTest1();
    void timeOut();


    void slotStopChecking();
    void setCurrBD_Number(quint8 val);
    void setLoadMSS(bool flag);

};

#endif // DCHECKPVD_H
