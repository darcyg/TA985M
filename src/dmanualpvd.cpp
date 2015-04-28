#include "dmanualpvd.h"

dManualPVD::dManualPVD(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    model = new DSDataModel(this);

    model -> setDataSize(256);

    tbBD -> setModel(model);

    tbBD -> updateGeometry();


    OnOffBoxes[0] = cbBD_A_On;
    OnOffBoxes[1] = cbBD_B_On;
    OnOffBoxes[2] = cbBD_V_On;
    OnOffBoxes[3] = cbBD_G_On;
    OnOffBoxes[4] = cbBD_D_On;


    connect(pbRead, SIGNAL(clicked()), this, SLOT(slot_readPVD()));
    connect(cbReadRegim, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangeRegime(int)));

    connect(cbStatus, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangeStatus(int)));

    connect(cbBD_A_On, SIGNAL(clicked()), this, SLOT(slot_ChangeOnOff()));
    connect(cbBD_B_On, SIGNAL(clicked()), this, SLOT(slot_ChangeOnOff()));
    connect(cbBD_V_On, SIGNAL(clicked()), this, SLOT(slot_ChangeOnOff()));
    connect(cbBD_G_On, SIGNAL(clicked()), this, SLOT(slot_ChangeOnOff()));
    connect(cbBD_D_On, SIGNAL(clicked()), this, SLOT(slot_ChangeOnOff()));

    connect(pbGetTest, SIGNAL(clicked()), this, SLOT(slot_GetTest()));

}

void dManualPVD::slot_ChangeRegime(int reg)
{

    model -> setDataSize(pSizeFromRegime[reg]);
    tbBD -> repaint();

    //TODO Add delete rows

}

void dManualPVD::slot_readPVD()
{

        noRead = true;

    emit getPVDData(rbPVD_Osn -> isChecked(), cbReadBD -> currentIndex(), cbReadLK -> currentIndex());


        model -> setDataSize(pSizeFromRegime[cbReadRegim -> currentIndex()]);



    qDebug() << "Waint for data";
    while (noRead)
    {
       // qDebug() << "1";
        QApplication::processEvents();
    }



    if (!ReadError)
    {

        qDebug() << "Read OK";
        for (int i = 0; i < pSizeFromRegime[cbReadRegim -> currentIndex()]; i++)
        {
            model -> BDData[i] = bd_data[i + pAddrFromRegime[cbReadRegim -> currentIndex()]];
        }
    } else
    {
        for (int i = 0; i < 256; i++)
            model -> BDData[i] = 255;
    }

}

void dManualPVD::slot_ReceivedMSS(quint8 *data)
{


    ReadError = false;


    qDebug() << Q_FUNC_INFO;

    for (int i =0; i < 256; i++)
        bd_data[i] = data[i];

    noRead = false;

}

void dManualPVD::slot_ErrorMSS()
{

    qDebug() << Q_FUNC_INFO;

    noRead = false;
    ReadError = true;

}

void dManualPVD::slot_ErrorModBus(quint8 err)
{
    qDebug() << Q_FUNC_INFO;
    noRead = false;
    ReadError = true;
}

void dManualPVD::slot_TestResult(bool All, bool PVD_A, bool PVD_B, bool PVD_V, bool PVD_G, bool PVD_D)
{

    ReadError = false;

    TestResult[0] = All;
    TestResult[1] = PVD_A;
    TestResult[2] = PVD_B;
    TestResult[3] = PVD_V;
    TestResult[4] = PVD_G;
    TestResult[5] = PVD_D;

    noRead = false;

}

void dManualPVD::slot_ChangeOnOff()
{
    quint8 OnOffData[5];


    for (int i = 0; i < 5; i++)
    {
        if (OnOffBoxes[i] -> isChecked())
        {
            OnOffData[i] = 1;
        } else
        {
            OnOffData[i] = 0;
        }
    }

    emit OnOffPVD(rbPVD_Osn -> isChecked(), OnOffData[0], OnOffData[1], OnOffData[2], OnOffData[3], OnOffData[4]);

}

void dManualPVD::slot_ChangeStatus(int status)
{
    emit ChangePVDStatus(rbPVD_Osn -> isChecked(), status);
}

void dManualPVD::slot_GetTest()
{
    if (cbStatus -> currentIndex() != 3)
    {
        QMessageBox::warning(this, tr("Внимание"), tr("Не установлен режим самоконтроля"), QMessageBox::Ok);
        return;
    }

    noRead = true;

    emit GetTest(rbPVD_Osn -> isChecked());

    while (noRead)
        QApplication::processEvents();

    if (!ReadError)
    {
        qDebug() << "Test read OK";

        if (TestResult[0])
        {
            qDebug() << "Test error";

            cbTestA -> setChecked(TestResult[1]);
            cbTestB -> setChecked(TestResult[2]);
            cbTestV -> setChecked(TestResult[3]);
            cbTestG -> setChecked(TestResult[4]);
            cbTestD -> setChecked(TestResult[5]);
        } else
        {
            qDebug() << "Test OK";
            cbTestA -> setChecked(false);
            cbTestB -> setChecked(false);
            cbTestV -> setChecked(false);
            cbTestG -> setChecked(false);
            cbTestD -> setChecked(false);
        }



    }
}
