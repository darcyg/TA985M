#ifndef DMANUALKOMMSS_H
#define DMANUALKOMMSS_H

#include "ui_dmanualkommss.h"

#include <QButtonGroup>
#include <QSignalMapper>
#include <QMessageBox>

class dManualKomMSS : public QDialog, private Ui::dManualKomMSS
{
    Q_OBJECT


private:

    QButtonGroup *MSSA_Group;
    QButtonGroup *MSSB_Group;
    QButtonGroup *MSSV_Group;
    QButtonGroup *MSSG_Group;
    QButtonGroup *MSSD_Group;

    QButtonGroup *MSS_Group[5];


    QSignalMapper *ButtonMapper;

    quint8 MSSOsnRes_Old[5];

    quint8 MBError;

public:
    explicit dManualKomMSS(QWidget *parent = 0);


public slots:

    void slotMSSSwitch(int btnId);

    void slotSwitchOK();
    void slotMBError(quint8 err);

signals:

    void MSSSwitch(quint8 mss, quint8 OsnRes);
};

#endif // DMANUALKOMMSS_H
