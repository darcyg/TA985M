#include "dselftest.h"

void dSelfTest::stoppingCheck()
{

    CheckTimer -> stop();


    setOK = false; setError = false;
// -==== Off PVD1 ====-
    emit setPVDStatus(true, 0);

    while(!setOK & !setError)
        QApplication::processEvents();

// -==== Off PVD2 ====-
    emit setPVDStatus(false, 0);

    while(!setOK & !setError)
        QApplication::processEvents();

// -==== Off MSS11 ====-

    emit setMSSSelfTest(0, false, false, false, false);

    while(!setOK & !setError)
        QApplication::processEvents();

// -==== Off MSS12 ====-

     emit setMSSSelfTest(1, false, false, false, false);

     while(!setOK & !setError)
        QApplication::processEvents();

// -==== Off MSS13 ====-

      emit setMSSSelfTest(2, false, false, false, false);

      while(!setOK & !setError)
        QApplication::processEvents();


// -==== Off MSS14 ====-

       emit setMSSSelfTest(3, false, false, false, false);

       while(!setOK & !setError)
         QApplication::processEvents();

// -==== Off MSS15 ====-

       emit setMSSSelfTest(4, false, false, false, false);

       while(!setOK & !setError)
         QApplication::processEvents();



    doTest = false;

    progressBar -> setHidden(true);

    pbStartTest -> setEnabled(true);
    pbStopTest -> setDisabled(true);

}

void dSelfTest::startingCheck()
{
    if (cbPVD1Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lPVD1Result, QString(tr("ПВД1")));
    if (cbPVD2Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lPVD2Result, QString(tr("ПВД2")));

    if (cbMAG1Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMAG1Result, QString(tr("МАГ1")));
    if (cbMAG2Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMAG2Result, QString(tr("МАГ2")));

    if (cbMSS1Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMSS1Result, QString(tr("МСС1")));
    if (cbMSS2Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMSS2Result, QString(tr("МСС2")));
    if (cbMSS3Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMSS3Result, QString(tr("МСС3")));
    if (cbMSS4Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMSS4Result, QString(tr("МСС4")));
    if (cbMSS5Test -> isChecked()) SET_LABEL_YELLOW_TEXT(lMSS5Result, QString(tr("МСС5")));

    progressBar -> setVisible(true);
    progressBar -> setValue(0);


}

dSelfTest::dSelfTest(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    progressBar -> setHidden(true);


    doTest = false;

    CheckTimer = new QTimer(this);


    connect(cbPVD1Test, SIGNAL(stateChanged(int)), this, SLOT(ChangePVD1()));
    connect(cbPVD2Test, SIGNAL(stateChanged(int)), this, SLOT(ChangePVD2()));
    connect(cbMAG1Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMAG1()));
    connect(cbMAG2Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMAG2()));
    connect(cbMSS1Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMSS1()));
    connect(cbMSS2Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMSS2()));
    connect(cbMSS3Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMSS3()));
    connect(cbMSS4Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMSS4()));
    connect(cbMSS5Test, SIGNAL(stateChanged(int)), this, SLOT(ChangeMSS5()));



    SET_LABEL_GREY_TEXT(lPVD1Result, QString(tr("ПВД1")));
    SET_LABEL_GREY_TEXT(lPVD2Result, QString(tr("ПВД2")));

    SET_LABEL_GREY_TEXT(lMAG1Result, QString(tr("МАГ1")));
    SET_LABEL_GREY_TEXT(lMAG2Result, QString(tr("МАГ2")));

    SET_LABEL_GREY_TEXT(lMSS1Result, QString(tr("МСС1")));
    SET_LABEL_GREY_TEXT(lMSS2Result, QString(tr("МСС2")));
    SET_LABEL_GREY_TEXT(lMSS3Result, QString(tr("МСС3")));
    SET_LABEL_GREY_TEXT(lMSS4Result, QString(tr("МСС4")));
    SET_LABEL_GREY_TEXT(lMSS5Result, QString(tr("МСС5")));


    connect(CheckTimer, SIGNAL(timeout()), this, SLOT(OnTimeOut()));

    connect(pbStartTest, SIGNAL(clicked()), this, SLOT(StartTest()));
    connect(pbStopTest, SIGNAL(clicked()), this, SLOT(StopTest()));
    connect(pbClose, SIGNAL(clicked()), this, SLOT(accept()));
}

void dSelfTest::setControl(bool cnt)
{
    cbPVD1Test -> setEnabled(cnt);
    cbPVD2Test -> setEnabled(cnt);
    cbMAG1Test -> setEnabled(cnt);
    cbMAG2Test -> setEnabled(cnt);
    cbMSS1Test -> setEnabled(cnt);
    cbMSS2Test -> setEnabled(cnt);
    cbMSS3Test -> setEnabled(cnt);
    cbMSS4Test -> setEnabled(cnt);
    cbMSS5Test -> setEnabled(cnt);

    sbCheckTime -> setEnabled(cnt);


}

void dSelfTest::ChangePVD1()
{
    if (cbPVD1Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lPVD1Result, QString(tr("ПВД1")));
    else
        SET_LABEL_GREY_TEXT(lPVD1Result, QString(tr("ПВД1")));
}

void dSelfTest::ChangePVD2()
{
    if (cbPVD2Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lPVD2Result, QString(tr("ПВД2")));
    else
        SET_LABEL_GREY_TEXT(lPVD2Result, QString(tr("ПВД2")));
}

void dSelfTest::ChangeMAG1()
{
    if (cbMAG1Test -> isChecked())
    {
        SET_LABEL_YELLOW_TEXT(lMAG1Result, QString(tr("МАГ1")));
        if (cbMAG2Test -> isChecked()) cbMAG2Test -> setChecked(false);
    }
    else
        SET_LABEL_GREY_TEXT(lMAG1Result, QString(tr("МАГ1")));


}

void dSelfTest::ChangeMAG2()
{
    if (cbMAG2Test -> isChecked())
    {
        SET_LABEL_YELLOW_TEXT(lMAG2Result, QString(tr("МАГ2")));
        if (cbMAG1Test -> isChecked()) cbMAG1Test -> setChecked(false);

    }
    else
        SET_LABEL_GREY_TEXT(lMAG2Result, QString(tr("МАГ2")));
}

void dSelfTest::ChangeMSS1()
{
    if (cbMSS1Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lMSS1Result, QString(tr("МСС1")));
    else
        SET_LABEL_GREY_TEXT(lMSS1Result, QString(tr("МСС1")));
}

void dSelfTest::ChangeMSS2()
{
    if (cbMSS2Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lMSS2Result, QString(tr("МСС2")));
    else
        SET_LABEL_GREY_TEXT(lMSS2Result, QString(tr("МСС2")));
}

void dSelfTest::ChangeMSS3()
{
    if (cbMSS3Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lMSS3Result, QString(tr("МСС3")));
    else
        SET_LABEL_GREY_TEXT(lMSS3Result, QString(tr("МСС3")));
}

void dSelfTest::ChangeMSS4()
{
    if (cbMSS4Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lMSS4Result, QString(tr("МСС4")));
    else
        SET_LABEL_GREY_TEXT(lMSS4Result, QString(tr("МСС4")));
}

void dSelfTest::ChangeMSS5()
{
    if (cbMSS5Test -> isChecked())
        SET_LABEL_YELLOW_TEXT(lMSS5Result, QString(tr("МСС5")));
    else
        SET_LABEL_GREY_TEXT(lMSS5Result, QString(tr("МСС5")));
}

void dSelfTest::StartTest()
{

    pbStartTest -> setDisabled(true);
    pbStopTest -> setEnabled(true);


    CheckStage = START;

    doTest = true;

    startingCheck();

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

 // =========================================================================================================================================================


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
                    SET_LABEL_RED_TEXT(lPVD1Result, QString(tr("ПВД1")));
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
                    SET_LABEL_RED_TEXT(lPVD1Result, QString(tr("ПВД1")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lPVD1Result, QString(tr("ПВД1")));
                    CheckStage = SET_PVD2;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for PVD1";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока ПВД1"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lPVD1Result, QString(tr("ПВД1")));
                    stoppingCheck();
                }
            }

            break;

// =========================================================================================================================================================


        case SET_PVD2:

            qDebug() << "SET_PVD2";

            if (cbPVD2Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_PVD;
                setOK = false;
                setError = false;
                emit setPVDStatus(false, 3);
                CheckStage = WAIT_FOR_SET_PVD2;
            } else
            {
                CheckStage = SET_MAG1;
            }

            break;

        case WAIT_FOR_SET_PVD2:

            qDebug() << "WAIT_FOR_SET_PVD2";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_PVD2;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest PVD2";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока ПВД2"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lPVD2Result, QString(tr("ПВД2")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_PVD2:

            qDebug() << "CHEKING_PVD2";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_PVD_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_PVD2;
                emit getPVDTestResult(false);
            }

            break;


        case CHECK_PVD2:


            qDebug() << "CHECK_PVD2";

            if (setOK)
            {
                qDebug() << "Get test PVD2 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля ПВД2"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки ПВД2 каналы: ");
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
                    SET_LABEL_RED_TEXT(lPVD2Result, QString(tr("ПВД2")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lPVD2Result, QString(tr("ПВД2")));
                    CheckStage = SET_MAG1;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for PVD2";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока ПВД2"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lPVD2Result, QString(tr("ПВД2")));
                    stoppingCheck();
                }
            }

            break;

// =========================================================================================================================================================
            case SET_MAG1:
            qDebug() << "SET_MAG1";

            if (cbMAG1Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_PVD;
                setOK = false;
                setError = false;
               // emit setMAGStatus(true, 3);
                CheckStage = WAIT_FOR_SET_MAG1;
            } else
            {
                CheckStage = SET_MAG2;
            }

            break;
                break;

// =========================================================================================================================================================

        case SET_MAG2:
        qDebug() << "SET_MAG2";

        if (cbMAG2Test -> isChecked())
        {

            wait_time = WAIT_TIME_FOR_SET_PVD;
            setOK = false;
            setError = false;
           // emit setMAGStatus(true, 3);
            CheckStage = WAIT_FOR_SET_MAG2;
        } else
        {
            CheckStage = SET_MSS1;
        }

        break;
            break;

// =========================================================================================================================================================

        case SET_MSS1:

            qDebug() << "SET_MSS1";

            if (cbMSS1Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_MSS;
                setOK = false;
                setError = false;
                emit setMSSSelfTest(0, true, true, true, true);
                CheckStage = WAIT_FOR_SET_MSS1;
            } else
            {
                CheckStage = SET_MSS2;
            }

            break;

        case WAIT_FOR_SET_MSS1:

            qDebug() << "WAIT_FOR_SET_MSS1";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_MSS1;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest MSS1";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС1"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS1Result, QString(tr("МСС1")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_MSS1:

            qDebug() << "CHEKING_MSS1";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_MSS_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_MSS1;
                emit getMSSTestResult(0);
            }

            break;


        case CHECK_MSS1:


            qDebug() << "CHECK_MSS1";

            if (setOK)
            {
                qDebug() << "Get test MSS1 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля  МСС1"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки МСС1 каналы: ");
                    if (MSS1_Result) ErrString.append(tr("А"));
                    if (MSS2_Result) {
                        if (MSS1_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }

                    if (MSS3_Result) {
                        if (MSS1_Result | MSS2_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }

                    if (MSS4_Result){
                        if (MSS1_Result | MSS2_Result | MSS3_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    SET_LABEL_RED_TEXT(lMSS1Result, QString(tr("МСС1")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lMSS1Result, QString(tr("МСС1")));
                    CheckStage = SET_MSS2;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for MSS1";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС1"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS1Result, QString(tr("МСС1")));
                    stoppingCheck();
                }
            }

            break;

// =========================================================================================================================================================
        case SET_MSS2:

            qDebug() << "SET_MSS2";

            if (cbMSS2Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_MSS;
                setOK = false;
                setError = false;
                emit setMSSSelfTest(1, true, true, true, true);
                CheckStage = WAIT_FOR_SET_MSS2;
            } else
            {
                CheckStage = SET_MSS3;
            }

            break;

        case WAIT_FOR_SET_MSS2:

            qDebug() << "WAIT_FOR_SET_MSS2";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_MSS2;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest MSS2";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС2"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS2Result, QString(tr("МСС2")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_MSS2:

            qDebug() << "CHEKING_MSS2";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_MSS_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_MSS2;
                emit getMSSTestResult(1);
            }

            break;


        case CHECK_MSS2:


            qDebug() << "CHECK_MSS2";

            if (setOK)
            {
                qDebug() << "Get test MSS2 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля  МСС2"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки МСС2 каналы: ");
                    if (MSS1_Result) ErrString.append(tr("А"));
                    if (MSS2_Result) {
                        if (MSS1_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }

                    if (MSS3_Result) {
                        if (MSS1_Result | MSS2_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }

                    if (MSS4_Result){
                        if (MSS1_Result | MSS2_Result | MSS3_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    SET_LABEL_RED_TEXT(lMSS2Result, QString(tr("МСС2")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lMSS2Result, QString(tr("МСС2")));
                    CheckStage = SET_MSS3;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for MSS2";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС2"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS2Result, QString(tr("МСС2")));
                    stoppingCheck();
                }
            }

            break;
// =========================================================================================================================================================

        case SET_MSS3:

            qDebug() << "SET_MSS3";

            if (cbMSS3Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_MSS;
                setOK = false;
                setError = false;
                emit setMSSSelfTest(2, true, true, true, true);
                CheckStage = WAIT_FOR_SET_MSS3;
            } else
            {
                CheckStage = SET_MSS4;
            }

            break;

        case WAIT_FOR_SET_MSS3:

            qDebug() << "WAIT_FOR_SET_MSS3";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_MSS3;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest MSS3";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС3"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS3Result, QString(tr("МСС3")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_MSS3:

            qDebug() << "CHEKING_MSS3";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_MSS_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_MSS3;
                emit getMSSTestResult(2);
            }

            break;


        case CHECK_MSS3:


            qDebug() << "CHECK_MSS3";

            if (setOK)
            {
                qDebug() << "Get test MSS3 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля  МСС3"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки МСС3 каналы: ");
                    if (MSS1_Result) ErrString.append(tr("А"));
                    if (MSS2_Result) {
                        if (MSS1_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }

                    if (MSS3_Result) {
                        if (MSS1_Result | MSS2_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }

                    if (MSS4_Result){
                        if (MSS1_Result | MSS2_Result | MSS3_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    SET_LABEL_RED_TEXT(lMSS3Result, QString(tr("МСС3")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lMSS3Result, QString(tr("МСС3")));
                    CheckStage = SET_MSS4;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for MSS3";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС3"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS3Result, QString(tr("МСС3")));
                    stoppingCheck();
                }
            }

            break;
// =========================================================================================================================================================

        case SET_MSS4:

            qDebug() << "SET_MSS4";

            if (cbMSS4Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_MSS;
                setOK = false;
                setError = false;
                emit setMSSSelfTest(3, true, true, true, true);
                CheckStage = WAIT_FOR_SET_MSS4;
            } else
            {
                CheckStage = SET_MSS5;
            }

            break;

        case WAIT_FOR_SET_MSS4:

            qDebug() << "WAIT_FOR_SET_MSS4";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_MSS4;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest MSS4";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС4"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS4Result, QString(tr("МСС4")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_MSS4:

            qDebug() << "CHEKING_MSS4";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_MSS_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_MSS4;
                emit getMSSTestResult(3);
            }

            break;


        case CHECK_MSS4:


            qDebug() << "CHECK_MSS4";

            if (setOK)
            {
                qDebug() << "Get test MSS4 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля  МСС4"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки МСС4 каналы: ");
                    if (MSS1_Result) ErrString.append(tr("А"));
                    if (MSS2_Result) {
                        if (MSS1_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }

                    if (MSS3_Result) {
                        if (MSS1_Result | MSS2_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }

                    if (MSS4_Result){
                        if (MSS1_Result | MSS2_Result | MSS3_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    SET_LABEL_RED_TEXT(lMSS4Result, QString(tr("МСС4")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lMSS4Result, QString(tr("МСС4")));
                    CheckStage = SET_MSS5;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for MSS4";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС4"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS4Result, QString(tr("МСС4")));
                    stoppingCheck();
                }
            }

            break;
// =========================================================================================================================================================

        case SET_MSS5:

            qDebug() << "SET_MSS5";

            if (cbMSS5Test -> isChecked())
            {

                wait_time = WAIT_TIME_FOR_SET_MSS;
                setOK = false;
                setError = false;
                emit setMSSSelfTest(4, true, true, true, true);
                CheckStage = WAIT_FOR_SET_MSS5;
            } else
            {
                CheckStage = END_TEST;
            }

            break;

        case WAIT_FOR_SET_MSS5:

            qDebug() << "WAIT_FOR_SET_MSS5";

            if (setOK)
            {
                qDebug() << "Set status OK";
                CheckStage = CHEKING_MSS5;
                check_time = sbCheckTime -> value();
            } else
            {
                wait_time--;

                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error set SelfTest MSS5";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС5"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS5Result, QString(tr("МСС5")));
                    stoppingCheck();
                    break;
                }


            }

            break;

        case CHEKING_MSS5:

            qDebug() << "CHEKING_MSS5";

            check_time--;
            progressBar -> setValue(progressBar -> value() + 1);

            if (check_time == 0)
            {
                wait_time = WAIT_TIME_FOR_GET_MSS_TEST;
                setOK = false;
                setError = false;
                CheckStage = CHECK_MSS5;
                emit getMSSTestResult(4);
            }

            break;


        case CHECK_MSS5:


            qDebug() << "CHECK_MSS5";

            if (setOK)
            {
                qDebug() << "Get test MSS5 OK";
                if (ALL_Result)
                {


                    ErrMes.setText(tr("Ошибка самоконтроля  МСС5"));
                    ErrMes.setStandardButtons(QMessageBox::Ok);
                    ErrString = tr("Ошибка проверки МСС5 каналы: ");
                    if (MSS1_Result) ErrString.append(tr("А"));
                    if (MSS2_Result) {
                        if (MSS1_Result)
                            ErrString.append(tr(", Б"));
                        else
                            ErrString.append(tr("Б"));
                    }

                    if (MSS3_Result) {
                        if (MSS1_Result | MSS2_Result)
                            ErrString.append(tr(", В"));
                        else
                            ErrString.append(tr("В"));
                    }

                    if (MSS4_Result){
                        if (MSS1_Result | MSS2_Result | MSS3_Result)
                            ErrString.append(tr(", Г"));
                        else
                            ErrString.append(tr("Г"));
                    }

                    ErrMes.setDetailedText(ErrString);

                    ErrMes.exec();
                    SET_LABEL_RED_TEXT(lMSS1Result, QString(tr("МСС1")));
                    stoppingCheck();


                } else
                {
                    SET_LABEL_GREEN_TEXT(lMSS5Result, QString(tr("МСС5")));
                    CheckStage = END_TEST;

                }
            } else
            {
                wait_time--;
                if (setError | (wait_time == 0))
                {
                    qDebug() << "Error receive SelfTest data for MSS5";
                    QMessageBox::critical(this, tr("Самоконтроль"), tr("Ошибка самоконтроля блока МСС5"), QMessageBox::Ok);
                    SET_LABEL_RED_TEXT(lMSS5Result, QString(tr("МСС5")));
                    stoppingCheck();
                }
            }

            break;
// =========================================================================================================================================================

        case END_TEST:

            QMessageBox::warning(this, tr("Самоконтрроль"), tr("Проварка самоконтроля ТК168 пройдена"), QMessageBox::Ok);
            stoppingCheck();
            break;

// =========================================================================================================================================================



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

void dSelfTest::slotChangeMSSSelfTestSetOK()
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

void dSelfTest::slotMSSTestResult(bool All, bool ch1, bool ch2, bool ch3, bool ch4)
{
    setOK = true;
    setError = false;
    ALL_Result = All;

    MSS1_Result = ch1;
    MSS2_Result = ch2;
    MSS3_Result = ch3;
    MSS4_Result = ch4;
}
