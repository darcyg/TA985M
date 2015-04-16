#include "dmanuamag.h"

dManuaMAG::dManuaMAG(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    model = new DSDataModel(this);

    model -> setDataSize(256);
    tbBD -> setModel(model);

    tbBD -> updateGeometry();

    connect(pbRead, SIGNAL(clicked()), this, SLOT(slot_readMAG()));


}

void dManuaMAG::slot_ChangeRegime(int reg)
{

}

void dManuaMAG::slot_readMAG()
{

}

void dManuaMAG::slot_ReceivedMSS(quint8 *data)
{

}

void dManuaMAG::slot_ErrorMSS()
{

}

void dManuaMAG::slot_ErrorModBus(quint8 err)
{

}
