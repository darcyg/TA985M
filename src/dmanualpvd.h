#ifndef DMANUALPVD_H
#define DMANUALPVD_H

#include "ui_dmanualpvd.h"


#include <QDebug>

#include "src/dsdatamodel.h"


quint16 const SizeFromRegime[4] = {256, 64, 64, 64};
quint16 const AddrFromRegime[4] = {0, 64, 128, 192};

class dManualPVD : public QDialog, private Ui::dManualPVD
{
    Q_OBJECT



private:

    bool noRead;
    bool ReadError;

    QCheckBox *OnOffBoxes[5];


public:
    explicit dManualPVD(QWidget *parent = 0);

    DSDataModel *model;

    quint8 bd_data[256];





public slots:


    void slot_ChangeRegime(int reg);

    void slot_readPVD();

    void slot_ReceivedMSS(quint8 *data);
    void slot_ErrorMSS();




    void slot_ChangeOnOff();
    void slot_ChangeStatus(int status);


signals:

    void getPVDData(quint16 numBD, quint16 numMSS);
    void OnOffPVD(bool OSN, quint8 PVD_A, quint8 PVD_B, quint8 PVD_V, quint8 PVD_G, quint8 PVD_D);
    void ChangePVDStatus(bool osn, quint8 status);

};

#endif // DMANUALPVD_H
