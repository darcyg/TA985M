#ifndef MODBUSTCP_H
#define MODBUSTCP_H

#include <QObject>
#include <QDebug>
#include "3rdparty/libmodbus/modbus.h"
#include "3rdparty/libmodbus/modbus-tcp.h"
#include <errno.h>

#include <QtCore/QtEndian>


typedef struct _BlockStatus {

    bool rstatus;
    bool status;
    quint8 SoftVersion;
    quint8 HardVersion;


} BLOCK_STATUS;


class ModBusTCP : public QObject
{
    Q_OBJECT

private:

    modbus_t *ctx;

    quint16 NumberOfRepeat;




public:
    explicit ModBusTCP(QObject *parent = 0);
    BLOCK_STATUS *ReportSlaveID(quint8 slave);

    void setRepeat(quint16 val) {NumberOfRepeat = val;}
    quint16 getRepeat() {return NumberOfRepeat;}


signals:

    void ModBusError(int errn);
    void ModBusOK();

public slots:

    void Connect();
    void DisConnect();
    void WriteHoldingRegister(quint16 slave, quint16 addr, quint16 value);
    void WriteCoil(quint16 slave, quint16 addr, quint8 value);
    void WriteMultipleHoldingRegisters(quint16 slave, quint16 addr, quint16 num, quint16 *data);
    void WriteMultipleCoils(quint16 slave, quint16 addr, quint16 num, quint8 *data);
    void ReadInputRegisters(quint16 slave, quint16 addr, quint16 size, quint16 *data);
    void ReadMultipleCoils(quint16 slave, quint16 addr, quint16 size, quint8 *data);
    void ReadDiscreteInputs(quint16 slave, quint16 addr, quint16 size, quint8 *data);



};

#endif // MODBUSTCP_H
