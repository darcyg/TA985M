#ifndef DMANUAMAG_H
#define DMANUAMAG_H

#include "ui_dmanuamag.h"


#include <QDebug>
#include <QMessageBox>

#include "src/dsdatamodel.h"

quint16 const SizeFromRegime[4] = {255, 64, 64, 64};
quint16 const AddrFromRegime[4] = {0, 64, 128, 192};

class dManuaMAG : public QDialog, private Ui::dManuaMAG
{
    Q_OBJECT


private:

    bool noRead;
    bool ReadError;



public:
    explicit dManuaMAG(QWidget *parent = 0);

    DSDataModel *model;
    quint8 bd_data[256];


public slots:

    void slot_ChangeRegime(int reg);
    void slot_readMAG();

    void slot_ReceivedMSS(quint8 *data);
    void slot_ErrorMSS();
    void slot_ErrorModBus(quint8 err);


signals:


};

#endif // DMANUAMAG_H
