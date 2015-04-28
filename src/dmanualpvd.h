#ifndef DMANUALPVD_H
#define DMANUALPVD_H

#include "ui_dmanualpvd.h"


#include <QDebug>
#include <QMessageBox>

#include "src/dsdatamodel.h"

quint16 const pSizeFromRegime[4] = {256, 64, 64, 64};
quint16 const pAddrFromRegime[4] = {0, 64, 128, 192};


class dManualPVD : public QDialog, private Ui::dManualPVD
{
    Q_OBJECT



private:



    bool noRead;
    bool ReadError;


    bool TestResult[6];

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
    void slot_ErrorModBus(quint8 err);

    void slot_TestResult(bool All, bool PVD_A, bool PVD_B, bool PVD_V, bool PVD_G, bool PVD_D);




    void slot_ChangeOnOff();
    void slot_ChangeStatus(int status);
    void slot_GetTest();


signals:

    void getPVDData(bool osn, quint16 numBD, quint16 numMSS);
    void OnOffPVD(bool OSN, quint8 PVD_A, quint8 PVD_B, quint8 PVD_V, quint8 PVD_G, quint8 PVD_D);
    void ChangePVDStatus(bool osn, quint8 status);
    void GetTest(bool osn);


};

#endif // DMANUALPVD_H
