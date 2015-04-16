#include "dselftest.h"

void dSelfTest::stoppingCheck()
{

    pbStartTest -> setEnabled(true);
    pbStopTest -> setDisabled(true);

    CheckTimer -> stop();
    doTest = false;
}

dSelfTest::dSelfTest(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    doTest = false;

    CheckTimer = new QTimer(this);

    connect(CheckTimer, SIGNAL(timeout()), this, SLOT(OnTimeOut()));

    connect(pbStartTest, SIGNAL(clicked()), this, SLOT(StartTest()));
    connect(pbStopTest, SIGNAL(clicked()), this, SLOT(StopTest()));
}

void dSelfTest::StartTest()
{

    pbStartTest -> setDisabled(true);
    pbStopTest -> setEnabled(true);


    CheckStage = START;

    doTest = true;

    CheckTimer -> start(500);



}

void dSelfTest::StopTest()
{
    pbStartTest -> setEnabled(true);
    pbStopTest -> setDisabled(true);

    doTest = false;

}

void dSelfTest::OnTimeOut()
{


    QMessageBox ErrMes;
    QString ErrString;

    if (doTest)
    {

        switch (CheckStage)
        {
        case START:

            qDebug() << "START";

            AllCheckTime = 0;

            if (cbPVD1Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbPVD2Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMAG1Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMAG2Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMSS1Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMSS2Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMSS3Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMSS4Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;
            if (cbMSS5Test -> isChecked()) AllCheckTime = AllCheckTime + sbCheckTime -> value() * 2;

            progressBar -> setMaximum(AllCheckTime);
            progressBar -> setValue(0);

            CheckStage = SET_PVD1;

            break;

        case SET_PVD1:

            qDebug() << "SET_PVD1";

            if (cbPVD1Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_PVD;
                setOK = false;
                setError = false;
                emit setPVDStatus(true, 3);
                CheckStage = WAIT_FOR_SET_PVD1;
            } else
            {
                CheckStage = SET_PVD2;
            }

            break;

        case WAIT_FOR_SET_PVD1:

            qDebug() << "WAIT_FOR_SET_PVD1";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_PVD1;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest PVD1";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока ПВД1"), QMessageBox::Ok);
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_PVD1:

            qDebug() << "CHEKING_PVD1";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_PVD_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_PVD1;
                emit getPVDTestResult(true);
            }

            break;


        case CHECK_PVD1:


            qDebug() << "CHECK_PVD1";

            if (setOK)
            {
                qDebug() << "Get test PVD1 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля ПВД1"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки ПВД1 каналы: ");
                    if (PVDA_Result) ErrString.append(tr("А"));
                    if (PVDB_Result) {
                        if (PVDA_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }
                    if (PVDV_Result) {
                        if (PVDA_Result | PVDB_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }
                    if (PVDG_Result){
                        if (PVDA_Result | PVDB_Result | PVDV_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }
                    if (PVDD_Result){
                        if (PVDA_Result | PVDB_Result | PVDV_Result | PVDG_Result)
                            ErrString.append(tr(", Д"));
                        else
                            ErrString.append(tr("Д"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    stoppingCheck();


                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for PVD1";
                }
            }

            break;

        case SET_PVD2:

            break;

        case CHECK_PVD2:

            break;
        }


    } else
    {
        CheckTimer -> stop();
    }

}

void dSelfTest::slotChangePVDStatusOK()
{
    setOK = true;
    setError = false;
}

void dSelfTest::slotModBusError(quint8 error)
{
    setOK = false;
    setError = true;

}

void dSelfTest::slotPVDTestResult(bool All, bool PVD_A, bool PVD_B, bool PVD_V, bool PVD_G, bool PVD_D)
{

    setOK = true;
    setError = false;
    ALL_Result = All;

    PVDA_Result = PVD_A;
    PVDB_Result = PVD_B;
    PVDV_Result = PVD_V;
    PVDG_Result = PVD_G;
    PVDD_Result = PVD_D;

}
