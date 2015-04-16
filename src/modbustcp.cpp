#include "modbustcp.h"


ModBusTCP::ModBusTCP(QObject *parent) :
    QObject(parent)
{

    ctx = modbus_new_tcp("192.168.3.236", 1502);

    if (ctx == NULL)
    {
        qDebug() << "Unable to allocate libmodbus context";
        return;
    }

}

void ModBusTCP::Connect()
{
    if (ctx != NULL)
    {
        if (modbus_connect(ctx) == -1)
        {
            qDebug() << "Connection failed: " << modbus_strerror(errno);
            return;
        }
    }

}

void ModBusTCP::WriteHoldingRegister(quint16 slave, quint16 addr, quint16 value)
{

    quint16 repeat = NumberOfRepeat;

    qDebug() << "Write HoldingRegister from slave: " << slave << "Addr: " << addr;

    while(repeat)
    {
        if (modbus_set_slave(ctx, slave) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error set slave: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    repeat = NumberOfRepeat;

    while (repeat)
    {

        if (modbus_write_register(ctx, addr, value) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error write HoldingRegister: " << errno;
                emit ModBusError(errno);
                return;
            }
        }else
        {
            repeat = 0;
        }
    }

     qDebug() << "Write OK" << repeat;
     emit ModBusOK();


}

void ModBusTCP::WriteMultipleHoldingRegisters(quint16 slave, quint16 addr, quint16 num, quint16 *data)
{

    quint16 tmp_data[128];
    quint16 repeat = NumberOfRepeat;


    qDebug() << "Write MultiHoldingRegisters from slave: " << slave << " Addr: " << addr << " Number: " << num;

    while(repeat)
    {
        if (modbus_set_slave(ctx, slave) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error set slave: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    for (int i = 0; i < num; i++)
    {
        tmp_data[i] = qToBigEndian<quint16>(data[i]);
    }

    repeat = NumberOfRepeat;

    while(repeat)
    {
        if (modbus_write_registers(ctx, addr, num, tmp_data) == -1)
        {

            if (--repeat == 0)
            {

                qDebug() << "Error write HoldingRegisters: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }
    qDebug() << "Write OK" << repeat;
    emit ModBusOK();

}

void ModBusTCP::WriteMultipleCoils(quint16 slave, quint16 addr, quint16 num, quint8 *data)
{

    quint16 repeat = NumberOfRepeat;

    qDebug() << "Write multiCoils from slave: " << slave << "Addr: " << addr << " number: " << num;

    while(repeat)
    {
        if (modbus_set_slave(ctx, slave) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error set slave: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    repeat = NumberOfRepeat;

    while (repeat)
    {

        qDebug() << Q_FUNC_INFO << repeat;
        if (modbus_write_bits(ctx, addr, num, data) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error write MultiCoils: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }
    qDebug() << "Write OK" << repeat;
    emit ModBusOK();

}

BLOCK_STATUS *ModBusTCP::ReportSlaveID(quint8 slave)
{

    uint8_t dest[10];
    int rc;
    BLOCK_STATUS *st = new BLOCK_STATUS;

    modbus_set_slave(ctx, slave);

    rc = modbus_report_slave_id(ctx, dest);

    qDebug() << "RC: " << rc;

    if (rc != -1)
    {



        st -> rstatus = true;
        if (dest[0]) st -> status = true; else st -> status = false;

        st -> SoftVersion = dest[1];
        st -> HardVersion = dest[2];

    } else
    {
        st -> rstatus = false;
    }


    return st;
}

void ModBusTCP::ReadInputRegisters(quint16 slave, quint16 addr, quint16 size, quint16 *data)
{

    quint16 repeat = NumberOfRepeat;


    while(repeat)
    {
        if (modbus_set_slave(ctx, slave) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error set slave: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    repeat = NumberOfRepeat;


    while(repeat)
    {

        if (modbus_read_input_registers(ctx, addr, size, data) == -1)
        {
            if (--repeat)
            {
                qDebug() << "Error read InputRegisters: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }
    qDebug() << "Read OK" << repeat;
    emit ModBusOK();

}

void ModBusTCP::ReadDiscreteInputs(quint16 slave, quint16 addr, quint16 size, quint8 *data)
{

    quint16 repeat = NumberOfRepeat;

    while(repeat)
    {
        if (modbus_set_slave(ctx, slave) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error set slave: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    repeat = NumberOfRepeat;

    while(repeat)
    {
        if (modbus_read_input_bits(ctx, addr, size, data) == -1)
        {
            if (--repeat == 0)
            {
                qDebug() << "Error read DiscreteInputs: " << errno;
                emit ModBusError(errno);
                return;
            }
        } else
        {
            repeat = 0;
        }
    }

    qDebug() << "Read OK" << repeat;
    emit ModBusOK();
}


