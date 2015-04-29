#include "dmanualkommss.h"

dManualKomMSS::dManualKomMSS(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    for(int i = 0; i < 5; i++)
    {
        MSSOsnRes_Old[i] = 0;
    }

    MSSA_Group = new QButtonGroup(this);
    MSSB_Group = new QButtonGroup(this);
    MSSV_Group = new QButtonGroup(this);
    MSSG_Group = new QButtonGroup(this);
    MSSD_Group = new QButtonGroup(this);

    ButtonMapper = new QSignalMapper(this);


    MSSA_Group -> addButton(rbMSSA_osn, 0);
    MSSA_Group -> addButton(rbMSSA_res, 1);
    MSS_Group[0] = MSSA_Group;

    MSSB_Group -> addButton(rbMSSB_osn, 0);
    MSSB_Group -> addButton(rbMSSB_res, 1);
    MSS_Group[1] = MSSB_Group;

    MSSV_Group -> addButton(rbMSSV_osn, 0);
    MSSV_Group -> addButton(rbMSSV_res, 1);
    MSS_Group[2] = MSSV_Group;

    MSSG_Group -> addButton(rbMSSG_osn, 0);
    MSSG_Group -> addButton(rbMSSG_res, 1);
    MSS_Group[3] = MSSG_Group;

    MSSD_Group -> addButton(rbMSSD_osn, 0);
    MSSD_Group -> addButton(rbMSSD_res, 1);
    MSS_Group[4] = MSSD_Group;


    connect(rbMSSA_osn, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSA_osn, 0);
    connect(rbMSSA_res, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSA_res, 1);

    connect(rbMSSB_osn, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSB_osn, 10);
    connect(rbMSSB_res, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSB_res, 11);

    connect(rbMSSV_osn, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSV_osn, 20);
    connect(rbMSSV_res, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSV_res, 21);

    connect(rbMSSG_osn, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSG_osn, 30);
    connect(rbMSSG_res, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSG_res, 31);

    connect(rbMSSD_osn, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSD_osn, 40);
    connect(rbMSSD_res, SIGNAL(clicked()), ButtonMapper, SLOT(map()));
    ButtonMapper -> setMapping(rbMSSD_res, 41);

    connect(ButtonMapper, SIGNAL(mapped(int)), this, SLOT(slotMSSSwitch(int)));



}

void dManualKomMSS::slotMSSSwitch(int btnId)
{

    quint8 mssNum;
    quint8 OsnRes;


    mssNum = btnId / 10;
    OsnRes = btnId % 10;

    MBError = 255;

    this -> setDisabled(true);
    emit MSSSwitch(mssNum, OsnRes);

    while (MBError == 255) {
        QApplication::processEvents();
    }

    if (MBError != 0)
    {
        QMessageBox::critical(this, tr("Ручное управление комутатором МСС"), tr("Ошибка обмена ModBus"), QMessageBox::Ok);
        MSS_Group[mssNum] -> button(MSSOsnRes_Old[mssNum])->setChecked(true);
    } else
    {
        MSSOsnRes_Old[mssNum] = OsnRes;
    }

    this -> setEnabled(true);

}

void dManualKomMSS::slotSwitchOK()
{
    MBError = 0;
}

void dManualKomMSS::slotMBError(quint8 err)
{
    MBError = err;
}




