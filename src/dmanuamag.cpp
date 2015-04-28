#include "dmanuamag.h"

dManuaMAG::dManuaMAG(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    last_Status = 0;

    model = new DSDataModel(this);

    model -> setDataSize(256);
    tbBD -> setModel(model);

    tbBD -> updateGeometry();

    connect(pbRead, SIGNAL(clicked()), this, SLOT(slot_readMAG()));

    connect(cbRegim, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ChangeStatus(int)));

}

void dManuaMAG::slot_ChangeRegime(int reg)
{

}

void dManuaMAG::slot_readMAG()
{

    MBResult = 255;

    emit getMAGData(cbReadLK -> currentIndex());

    model -> setDataSize(SizeFromRegime[cbReadRegim -> currentIndex()]);

    qDebug() << "Wait for data";

    while(MBResult == 255)
    {
        QApplication::processEvents();
    }

    if (MBResult == 0)
    {
        qDebug() << "Read OK";

        for (int i = 0; i < SizeFromRegime[cbReadRegim -> currentIndex()]; i++)
        {
            model -> BDData[i] = bd_data[i + AddrFromRegime[cbReadRegim -> currentIndex()]];
        }
    }

}

void dManuaMAG::slot_ReceivedMSS(quint8 *data)
{

    qDebug() << Q_FUNC_INFO;

    for(int i = 0; i < 256; i++)
        bd_data[i] = data[i];

    MBResult = 0;

}

void dManuaMAG::slot_ErrorMSS()
{

    qDebug() << Q_FUNC_INFO;
    MBResult = 1;
}

void dManuaMAG::slot_ErrorModBus(quint8 err)
{
    qDebug() << Q_FUNC_INFO << err;
    MBResult = err;

}

void dManuaMAG::slot_ChangeStatus(int status)
{

    if (status == last_Status) return;

    MBResult = 255;

    emit ChangeStatus(status);

    while(MBResult == 255)
        QApplication::processEvents();

    if (MBResult != 0)
    {
        QMessageBox::critical(this, tr("Ручное управление МАГ"), tr("Ошибка установки режима МАГ"), QMessageBox::Ok);
        cbRegim -> setCurrentIndex(last_Status);
    } else
    {
        last_Status = status;
    }

}

void dManuaMAG::slot_MAGChangeStatusOK()
{

}
