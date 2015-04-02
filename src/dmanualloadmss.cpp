#include "dmanualloadmss.h"

dManualLoadMSS::dManualLoadMSS(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    connect(pbOnOffMSS, SIGNAL(clicked()), this, SLOT(slotOnOffMSS()));
    connect(pbLoadMSS, SIGNAL(clicked()), this, SLOT(slotLoadMSS()));


}

void dManualLoadMSS::slotOnOffMSS()
{

    quint8 ch[4];

    if (cbChannal1 -> isChecked()) ch[0] = 1; else ch[0] = 0;
    if (cbChannal2 -> isChecked()) ch[1] = 1; else ch[1] = 0;
    if (cbChannal3 -> isChecked()) ch[2] = 1; else ch[2] = 0;
    if (cbChannal4 -> isChecked()) ch[3] = 1; else ch[3] = 0;

    emit wrMultipleCoils(slaveAddr[sbNumMSSfOnOff -> value()], 0, 4, ch);

}

void dManualLoadMSS::slotLoadMSS()
{

}
