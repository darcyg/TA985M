#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QMenu>
#include <QContextMenuEvent>
#include <QSettings>
#include <QSignalMapper>
#include <QDir>
#include <QMessageBox>

#include "src/viewbd.h"
#include "src/dmanualloadmss.h"
#include "src/dmssfileset.h"

#include "src/dselftest.h"


#include "src/modbustcp.h"
#include "tk168_config.h"
#include "src/dmanualpvd.h"

#include "src/ta985m.h"


static const char * msgType[] =
{
    "(II) ", // Info
    "(WW) ", // Warning
    "(EE) ", // Error
    "(FF) "  // Fatal error

};


#define WAIT_FOR_MODBUS_TRANSMIT(X) while(X) {QApplication::processEvents();} \
    if (MBResult)                                                                                        \
    {                                                                                                    \
        QMessageBox::critical(this, tr("Ошибка ТК168"), tr("Ошибка обмена ModBus"), QMessageBox::Ok);   \
        return;                                                                                          \
    }

#define setCurrentRegimMSS1BDG(X) currentRegim[0][3] = X
#define setCurrentRegimMSS2BDG(X) currentRegim[1][3] = X
#define setCurrentRegimMSS3BDG(X) currentRegim[2][3] = X
#define setCurrentRegimMSS4BDG(X) currentRegim[3][3] = X

#define setCurrentRegimMSS1BDD(X) currentRegim[0][4] = X
#define setCurrentRegimMSS2BDD(X) currentRegim[1][4] = X
#define setCurrentRegimMSS3BDD(X) currentRegim[2][4] = X
#define setCurrentRegimMSS4BDD(X) currentRegim[3][4] = X

static const unsigned char BlockAddr[] = {1, 2};

 static  const QString regimeName[4] = {"Все", "Режим 1", "Режим 2", "Режим 3"};

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event);

private:

    volatile quint8 MBResult;

    quint8 debugLevel;

    QMenu *secretMenu;

    ModBusTCP *MBTcp;

    bool SelfTestControl;

    quint8 currentRegim[4][5];

    void MSSLoad(quint8 bd_num, quint8 regim1, quint8 regim2, quint8 regim3, quint8 regim4);

    void ChangeRegimMSS(quint16 num, quint8 regimeMSS1, quint8 regimeMSS2, quint8 regimeMSS3, quint8 regimeMSS4);
    void LoadMSSPVD(quint8 *data, quint8 num_bd, quint8 num_mss);
    bool CheckMSS(quint8 *data, quint8 Regime, quint8 FileMSS);
    void ReadSettings();                // Чтение основных настроек из главного файла
    void WriteSettings();               // Запись основных настроек в главный файл

    void ReadRegimSettings(int regim);  // Чтение настроек текущего режима
    void WriteRegimSettings(int regim); // Запись настроек в текущий режим

    QComboBox *MSSFile[4];


    QSignalMapper *rsMenuMapper;

    QString TextRegimSoft;              // Текстовое название текущего режима программы
    quint8 CurrentSoftRegimeNumber;     // Номер текущего режима программы
    QString SoftRegimFileName;          // Имя файла текщего режима программы

    quint8 MSS_Addr[5];


    QString MSSFileName[4];

    struct _BLOCK_ADDR{

        quint16 MBRepeat;

        quint16 PVD1;
        quint16 PVD2;

        quint16 MSS_ADDR[5];

        quint16 MAG_ADDR;

    }  Block_Addr;

    struct _SELF_TEST_SETUP{

        bool PVD1;
        bool PVD2;
        bool MAG1;
        bool MAG2;
        bool MSS1;
        bool MSS2;
        bool MSS3;
        bool MSS4;
        bool MSS5;

    } SelfTestConfig[2];





public:


    quint8 BDData[1024];


    explicit MainWindow(QWidget *parent = 0);
    QStandardItemModel *logModel;


    void setReport(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    quint8 data[MSS_BUFF_SIZE];


public slots:

    void slotStartCheck();

    void slotCheckPVD();

    void slotDebugMenu();
    void slotSelfTestControl(bool tt);
    void slotManulMSS();
    void slotSetMSSFileName();
    void slotManualPVD();
    void slotManualMAG();

    void slotSecretMenuView(QPoint pe);



    void slotLoadMSS(quint8 num, quint8 ch1, quint8 ch2, quint8 ch3, quint8 ch4);


    void slotConnect();
    void slotDisConnect();
    void slotReportSlave();
    void slotSelfTest1();
    void slotSelfTest2();

    void changeBDDLK1(int val);
    void changeBDDLK2(int val);
    void changeBDDLK3(int val);
    void changeBDDLK4(int val);

    void changeBDGLK1(int val);
    void changeBDGLK2(int val);
    void changeBDGLK3(int val);
    void changeBDGLK4(int val);

    void ManualLoadMSS();

    void slotSetRegimeSoft(int num);


    void slotReadPVD(quint16 numBD, quint16 numMSS);
    void slotOnOffPVD(bool osn, quint8 PVD_A, quint8 PVD_B, quint8 PVD_V, quint8 PVD_G, quint8 PVD_D);
    void slotGetPVDTestResult(bool osn);
    void slotChangePVDStatus(bool osn, quint8 status);


    void slotModBusError(int err);
    void slotModBusOk();


signals:

    void MSSData(quint8 *data);
    void PVDTestResult(bool All, bool PVD_A, bool PVD_B, bool PVD_V, bool PVD_G, bool PVD_D);
    void ErrorMSSLoad();
    void ChangePVDStatusOK();

    void ErrorModBus(quint8 err);

};

#endif // MAINWINDOW_H
