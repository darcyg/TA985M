#ifndef DSELFTEST_H
#define DSELFTEST_H

#include "ui_dselftest.h"

#include <QDebug>
#include <QTimer>
#include <QMessageBox>


#define WAIT_TIME_FOR_SET_PVD               4
#define WAIT_TIME_FOR_GET_PVD_TEST          4


#define SET_LABEL_RED_TEXT(X, Y)    X -> setText(QString("<font color=\"red\">%1</font>").arg(Y))
#define SET_LABEL_GREEN_TEXT(X, Y)    X -> setText(QString("<font color=\"green\">%1</font>").arg(Y))
#define SET_LABEL_YELLOW_TEXT(X, Y)  X -> setText(QString("<font color=\"yellow\">%1</font>").arg(Y))
#define SET_LABEL_GREY_TEXT(X, Y)    X -> setText(QString("<font color=\"grey\">%1</font>").arg(Y))


enum CHECK_STAGE {START,
                  SET_PVD1, WAIT_FOR_SET_PVD1, CHEKING_PVD1, CHECK_PVD1,
                  SET_PVD2, WAIT_FOR_SET_PVD2, CHEKING_PVD2, CHECK_PVD2,
                  SET_MAG1, WAIT_FOR_SET_MAG1, CHEKING_MAG1, CHECK_MAG1};

class dSelfTest : public QDialog, private Ui::dSelfTest
{
    Q_OBJECT

private:

    QTimer *CheckTimer;

    bool doTest;

    bool setOK;
    bool setError;


    bool PVDA_Result;
    bool PVDB_Result;
    bool PVDV_Result;
    bool PVDG_Result;
    bool PVDD_Result;

    bool ALL_Result;

    CHECK_STAGE CheckStage;

    quint32 check_time;
    quint32 wait_time;

    quint32 AllCheckTime;

    void stoppingCheck();
    void startingCheck();

public:
    explicit dSelfTest(QWidget *parent = 0);

    void setPVD1Test(bool val) {cbPVD1Test -> setChecked(val);}
    void setPVD2Test(bool val) {cbPVD2Test -> setChecked(val);}
    void setMAG1Test(bool val) {cbMAG1Test -> setChecked(val);}
    void setMAG2Test(bool val) {cbMAG2Test -> setChecked(val);}
    void setMSS1Test(bool val) {cbMSS1Test -> setChecked(val);}
    void setMSS2Test(bool val) {cbMSS2Test -> setChecked(val);}
    void setMSS3Test(bool val) {cbMSS3Test -> setChecked(val);}
    void setMSS4Test(bool val) {cbMSS4Test -> setChecked(val);}
    void setMSS5Test(bool val) {cbMSS5Test -> setChecked(val);}

    void setControl(bool cnt);


public slots:


    void ChangePVD1();
    void ChangePVD2();
    void ChangeMAG1();
    void ChangeMAG2();
    void ChangeMSS1();
    void ChangeMSS2();
    void ChangeMSS3();
    void ChangeMSS4();
    void ChangeMSS5();


    void StartTest();
    void StopTest();

    void OnTimeOut();

    void slotChangePVDStatusOK();
    void slotModBusError(quint8 error);

    void slotPVDTestResult(bool All, bool PVD_A, bool PVD_B, bool PVD_V, bool PVD_G, bool PVD_D);

signals:

    void setPVDStatus(bool osn, quint8 status);
    void getPVDTestResult(bool osn);
};

#endif // DSELFTEST_H
