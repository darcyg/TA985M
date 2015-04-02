#ifndef DMANUALLOADMSS_H
#define DMANUALLOADMSS_H

#include "ui_dmanualloadmss.h"

class dManualLoadMSS : public QDialog, private Ui::dManualLoadMSS
{
    Q_OBJECT

public:
    explicit dManualLoadMSS(QWidget *parent = 0);

    quint16 slaveAddr[5];

public slots:

    void slotOnOffMSS();
    void slotLoadMSS();


signals:

    void wrMultipleCoils(quint16 slave, quint16 addr, quint16 num, quint8 *data);
};

#endif // DMANUALLOADMSS_H
