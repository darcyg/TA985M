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

}

void dManualPVD::slot_ChangeRegime(int reg)
{

    model -> setDataSize(SizeFromRegime[reg]);
    tbBD -> repaint();

    //TODO Add delete rows

}

void dManualPVD::slot_readPVD()
{

        noRead = true;

    emit getPVDData(cbReadBD -> currentIndex(), cbReadLK -> currentIndex());


        model -> setDataSize(SizeFromRegime[cbReadRegim -> currentIndex()]);



    qDebug() << "Waint for data";
    while (noRead)
    {
       // qDebug() << "1";
        QApplication::processEvents();
    }



    if (!ReadError)
    {

        qDebug() << "Read OK";
        for (int i = 0; i < SizeFromRegime[cbReadRegim -> currentIndex()]; i++)
        {
            model -> BDData[i] = bd_data[i + AddrFromRegime[cbReadRegim -> currentIndex()]];
        }
    }

}

void dManualPVD::slot_ReceivedMSS(quint8 *data)
{

    noRead = false;
    ReadError = false;


    qDebug() << Q_FUNC_INFO;

    for (int i =0; i < 256; i++)
        bd_data[i] = data[i];

}

void dManualPVD::slot_ErrorMSS()
{

    qDebug() << Q_FUNC_INFO;

    noRead = false;
    ReadError = false;

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
