#include "mainwindow.h"

void MainWindow::closeEvent(QCloseEvent *event)
{


        WriteRegimSettings(CurrentSoftRegimeNumber);
        WriteSettings();
        event -> accept();
}

/*
 * Загрузка иммитаторов МСС
 *
 * bd_num - номер БД с 0
 * regim1...regim4 номера режимов для каналов 0 - канал отключен
 *
 *
 */


void MainWindow::MSSLoad(quint8 bd_num, quint8 regim1, quint8 regim2, quint8 regim3, quint8 regim4)
{
    quint8 currMSSAddr = Block_Addr.MSS_ADDR[bd_num];

    quint8 mb_data[MSS_BLOCK_WRITE];

    quint16 *dataTowrite = (quint16 *)mb_data;

    QFile *mss_file = new QFile;

    quint16 mbMSSAdrr;

    quint16 readNum;


    QString mssfilePath = QApplication::applicationDirPath() + "/MSS/";


    qDebug() << "Mss modbus addr: " << currMSSAddr;


    // Выключаем все МСС

    MBResult = 255;

    MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_ONOFF_ADDR, 4, mb_data);

    WAIT_FOR_MODBUS_TRANSMIT(MBResult)


    // Загружаем МСС1
    if (regim1) {
        mss_file -> setFileName(mssfilePath + MSSFileName[regim1]);



        qDebug() << "Load file to MSS1: " << mss_file -> fileName();

        mss_file -> open(QIODevice::ReadOnly);
        mbMSSAdrr = MSS_CHANAL1_ADDR;

        MBResult = 255;

        mb_data[0] = 0; mb_data[1] = 0;
        MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_CHANAL_ADDR, 2, mb_data);

        WAIT_FOR_MODBUS_TRANSMIT(MBResult)



        while (!mss_file -> atEnd())
        {
            readNum = mss_file -> read((char *)mb_data, MSS_BLOCK_WRITE);

            MBResult = 255;

            MBTcp -> WriteMultipleHoldingRegisters(currMSSAddr, mbMSSAdrr, readNum/2, dataTowrite);

            WAIT_FOR_MODBUS_TRANSMIT(MBResult)

            mbMSSAdrr = mbMSSAdrr + readNum/2;
        }

        mss_file -> close();

    }

    // Загружаем МСС2
    if (regim2) {
        mss_file -> setFileName(mssfilePath + MSSFileName[regim2]);
        //mss_file -> setFileName("test.mss");

        qDebug() << "Load file to MSS2: " << mss_file -> fileName();

        mss_file -> open(QIODevice::ReadOnly);
        mbMSSAdrr = MSS_CHANAL2_ADDR;

        MBResult = 255;

        mb_data[0] = 1; mb_data[1] = 0;
        MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_CHANAL_ADDR, 2, mb_data);

        WAIT_FOR_MODBUS_TRANSMIT(MBResult)

        while (!mss_file -> atEnd())
        {
            readNum = mss_file -> read((char *)mb_data, MSS_BLOCK_WRITE);

            MBResult = 255;

            MBTcp -> WriteMultipleHoldingRegisters(currMSSAddr, mbMSSAdrr, readNum/2, dataTowrite);

            WAIT_FOR_MODBUS_TRANSMIT(MBResult)

            mbMSSAdrr = mbMSSAdrr + readNum/2;
        }

        mss_file -> close();

    }

    // Загружаем МСС3
    if (regim3) {
        mss_file -> setFileName(mssfilePath + MSSFileName[regim3]);
        //mss_file -> setFileName("test.mss");

        qDebug() << "Load file to MSS3: " << mss_file -> fileName();

        mss_file -> open(QIODevice::ReadOnly);
        mbMSSAdrr = MSS_CHANAL3_ADDR;

        MBResult = 255;

        mb_data[0] = 0; mb_data[1] = 1;
        MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_CHANAL_ADDR, 2, mb_data);

        WAIT_FOR_MODBUS_TRANSMIT(MBResult)

        while (!mss_file -> atEnd())
        {
            readNum = mss_file -> read((char *)mb_data, MSS_BLOCK_WRITE);

            MBResult = 255;

            MBTcp -> WriteMultipleHoldingRegisters(currMSSAddr, mbMSSAdrr, readNum/2, dataTowrite);

            WAIT_FOR_MODBUS_TRANSMIT(MBResult)

            mbMSSAdrr = mbMSSAdrr + readNum/2;
        }

        mss_file -> close();
    }

    // Загружаем МСС4
    if (regim4) {

        mss_file -> setFileName(mssfilePath + MSSFileName[regim4]);
        //mss_file -> setFileName("test.mss");

        qDebug() << "Load file to MSS4: " << mss_file -> fileName();

        mss_file -> open(QIODevice::ReadOnly);
        mbMSSAdrr = MSS_CHANAL4_ADDR;


        MBResult = 255;

        mb_data[0] = 1; mb_data[1] = 1;
        MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_CHANAL_ADDR, 2, mb_data);

        WAIT_FOR_MODBUS_TRANSMIT(MBResult)

        while (!mss_file -> atEnd())
        {
            readNum = mss_file -> read((char *)mb_data, MSS_BLOCK_WRITE);

            MBResult = 255;

            MBTcp -> WriteMultipleHoldingRegisters(currMSSAddr, mbMSSAdrr, readNum/2, dataTowrite);

            WAIT_FOR_MODBUS_TRANSMIT(MBResult)

            mbMSSAdrr = mbMSSAdrr + readNum/2;
        }

        mss_file -> close();
    }


    // Включаем МСС

    mb_data[0] = regim1;
   // mb_data[1] = 0; mb_data[2] = 0; mb_data[3] = 0;


    MBResult = 255;

    mb_data[1] = regim2; mb_data[2] = regim3; mb_data[3] = regim4;
    MBTcp -> WriteMultipleCoils(currMSSAddr, MSS_ONOFF_ADDR, 4, mb_data);

    WAIT_FOR_MODBUS_TRANSMIT(MBResult)

    delete mss_file;

}

/*
 * Смена режима работы БД
 *
 * num                               - номер БД 0 - БД-Г, 1 - БД-Д
 * regimMSS1..regimMSS4              - номер режима от 1
 *
 */
void MainWindow::ChangeRegimMSS(quint16 num, quint8 regimeMSS1, quint8 regimeMSS2, quint8 regimeMSS3, quint8 regimeMSS4)
{



    qDebug() << "Изменение БД-" << num
             << "МСС1-" << regimeMSS1 << "МСС2-" << regimeMSS2
             << "МСС3-" << regimeMSS3 << "МСС4-" << regimeMSS4;


    if (num == 0) // Изменяем БД-Г

    {
        if (regimeMSS1)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKG_1, regimeMSS1);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS2)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKG_2, regimeMSS2);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS3)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKG_3, regimeMSS3);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS4)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKG_4, regimeMSS4);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
    } else // Изменяем БД-Д
    {
        if (regimeMSS1)
         {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKD_1, regimeMSS1);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS2)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKD_2, regimeMSS2);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS3)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKD_3, regimeMSS3);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
        if (regimeMSS4)
        {
            MBResult = 255;
            MBTcp -> WriteHoldingRegister(PVD_ADDR, ADDR_REGIM_LKD_4, regimeMSS4);
            WAIT_FOR_MODBUS_TRANSMIT(MBResult)
        }
    }
}


/*
 * Запрос данных одного МСС с БД
 *
 * data         - принятые данные   (Передается указатель с ыделенной памятью на 256 байт)
 * num_bd       - номер БД          с 0
 * num_mss      - номер МСС         с 0
 * RegimeMSS    - установленный режим МСС
 *
 * возврат      - успешна ли загрузка
 *
 */

void MainWindow::LoadMSSPVD(quint8 *data, quint8 num_bd, quint8 num_mss)
{


    quint16 Addr;  // Адрес данных МСС

    quint16 *data_t = (quint16 *)data;

    quint16 read_data[MSS_READ_BUFF_SIZE];

    Addr = num_bd * 128 + num_mss * MSS_BUFF_SIZE;

    for (int i = 0; i < MSS_BUFF_SIZE_WORD / MSS_READ_BUFF_SIZE; i++)  // Читаем порциями по 64 слова
    {
        Addr = num_bd * 128 + num_mss * MSS_BUFF_SIZE_WORD + i * MSS_READ_BUFF_SIZE;


        MBResult = 255;
        MBTcp -> ReadInputRegisters(PVD_ADDR, Addr, MSS_READ_BUFF_SIZE, read_data);

        WAIT_FOR_MODBUS_TRANSMIT(MBResult)

        for (int j = 0; j < MSS_READ_BUFF_SIZE; j++)
        {
            data_t[i * MSS_READ_BUFF_SIZE + j] = read_data[j];
        }

    }

    MBResult = 0;
    return;




}

bool MainWindow::CheckMSS(quint8 *data, quint8 Regime, quint8 FileMSS)
{

}


void MainWindow::ReadSettings()
{
    QSettings setupFile(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);



    setupFile.beginGroup("Regim_LK");

    currentRegim[0][0] = setupFile.value("BDA_LK1", 2).toInt();
    currentRegim[1][0] = setupFile.value("BDA_LK2", 1).toInt();
    currentRegim[2][0] = setupFile.value("BDA_LK3", 1).toInt();
    currentRegim[3][0] = setupFile.value("BDA_LK4", 2).toInt();

    currentRegim[0][1] = setupFile.value("BDB_LK1", 3).toInt();
    currentRegim[1][1] = setupFile.value("BDB_LK2", 1).toInt();
    currentRegim[2][1] = setupFile.value("BDB_LK3", 1).toInt();
    currentRegim[3][1] = setupFile.value("BDB_LK4", 2).toInt();

    currentRegim[0][2] = setupFile.value("BDV_LK1", 2).toInt();
    currentRegim[1][2] = setupFile.value("BDV_LK2", 1).toInt();
    currentRegim[2][2] = setupFile.value("BDV_LK3", 1).toInt();
    currentRegim[3][2] = setupFile.value("BDV_LK4", 2).toInt();



    setupFile.endGroup();

    setupFile.beginGroup("Blocks_ADDR");

        Block_Addr.PVD1 = setupFile.value("PVD1", 24).toInt();
        Block_Addr.PVD2 = setupFile.value("PVD2", 25).toInt();

        Block_Addr.MSS_ADDR[0] = setupFile.value("MSS1", 2).toInt();
        Block_Addr.MSS_ADDR[1] = setupFile.value("MSS2", 3).toInt();
        Block_Addr.MSS_ADDR[2] = setupFile.value("MSS3", 4).toInt();
        Block_Addr.MSS_ADDR[3] = setupFile.value("MSS4", 5).toInt();
        Block_Addr.MSS_ADDR[4] = setupFile.value("MSS5", 6).toInt();

        Block_Addr.MAG_ADDR = setupFile.value("MAG", 33).toInt();

    setupFile.endGroup();


    setupFile.beginGroup("SelfTest1");

        SelfTestConfig[0].PVD1 = setupFile.value("PVD1", true).toBool();
        SelfTestConfig[0].PVD2 = setupFile.value("PVD2", true).toBool();
        SelfTestConfig[0].MAG1 = setupFile.value("MAG1", true).toBool();
        SelfTestConfig[0].MAG2 = setupFile.value("MAG2", false).toBool();
        SelfTestConfig[0].MSS1 = setupFile.value("MSS1", true).toBool();
        SelfTestConfig[0].MSS2 = setupFile.value("MSS2", true).toBool();
        SelfTestConfig[0].MSS3 = setupFile.value("MSS3", true).toBool();
        SelfTestConfig[0].MSS4 = setupFile.value("MSS4", true).toBool();
        SelfTestConfig[0].MSS5 = setupFile.value("MSS5", true).toBool();

    setupFile.endGroup();

    setupFile.beginGroup("SelfTest2");

        SelfTestConfig[1].PVD1 = setupFile.value("PVD1", false).toBool();
        SelfTestConfig[1].PVD2 = setupFile.value("PVD2", false).toBool();
        SelfTestConfig[1].MAG1 = setupFile.value("MAG1", false).toBool();
        SelfTestConfig[1].MAG2 = setupFile.value("MAG2", true).toBool();
        SelfTestConfig[1].MSS1 = setupFile.value("MSS1", false).toBool();
        SelfTestConfig[1].MSS2 = setupFile.value("MSS2", false).toBool();
        SelfTestConfig[1].MSS3 = setupFile.value("MSS3", false).toBool();
        SelfTestConfig[1].MSS4 = setupFile.value("MSS4", false).toBool();
        SelfTestConfig[1].MSS5 = setupFile.value("MSS5", false).toBool();

    setupFile.endGroup();


    setupFile.beginGroup("ModBus");

    Block_Addr.MBRepeat = setupFile.value("NumberOfRepeat", 3).toInt();


    setupFile.endGroup();


}

void MainWindow::WriteSettings()
{
    QSettings setupFile(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);

       qDebug() << setupFile.fileName();

       setupFile.beginGroup("Regim_LK");

        setupFile.setValue("BDG_LK1", currentRegim[0][3]);
        setupFile.setValue("BDG_LK2", currentRegim[1][3]);
        setupFile.setValue("BDG_LK3", currentRegim[2][3]);
        setupFile.setValue("BDG_LK4", currentRegim[3][3]);

        setupFile.setValue("BDD_LK1", currentRegim[0][4]);
        setupFile.setValue("BDD_LK2", currentRegim[1][4]);
        setupFile.setValue("BDD_LK3", currentRegim[2][4]);
        setupFile.setValue("BDD_LK4", currentRegim[3][4]);

       setupFile.endGroup();

       setupFile.beginGroup("Blocks_ADDR");

        setupFile.setValue("PVD1", Block_Addr.PVD1);
        setupFile.setValue("PVD2", Block_Addr.PVD2);

        setupFile.setValue("MSS1", Block_Addr.MSS_ADDR[0]);
        setupFile.setValue("MSS2", Block_Addr.MSS_ADDR[1]);
        setupFile.setValue("MSS3", Block_Addr.MSS_ADDR[2]);
        setupFile.setValue("MSS4", Block_Addr.MSS_ADDR[3]);
        setupFile.setValue("MSS5", Block_Addr.MSS_ADDR[4]);

        setupFile.setValue("MAG", Block_Addr.MAG_ADDR);

       setupFile.endGroup();


       setupFile.beginGroup("SelfTest1");

           setupFile.setValue("PVD1", SelfTestConfig[0].PVD1);
           setupFile.setValue("PVD2", SelfTestConfig[0].PVD2);
           setupFile.setValue("MAG1", SelfTestConfig[0].MAG1);
           setupFile.setValue("MAG2", SelfTestConfig[0].MAG2);
           setupFile.setValue("MSS1", SelfTestConfig[0].MSS1);
           setupFile.setValue("MSS2", SelfTestConfig[0].MSS2);
           setupFile.setValue("MSS3", SelfTestConfig[0].MSS3);
           setupFile.setValue("MSS4", SelfTestConfig[0].MSS4);
           setupFile.setValue("MSS5", SelfTestConfig[0].MSS5);

       setupFile.endGroup();

       setupFile.beginGroup("SelfTest2");

           setupFile.setValue("PVD1", SelfTestConfig[1].PVD1);
           setupFile.setValue("PVD2", SelfTestConfig[1].PVD2);
           setupFile.setValue("MAG1", SelfTestConfig[1].MAG1);
           setupFile.setValue("MAG2", SelfTestConfig[1].MAG2);
           setupFile.setValue("MSS1", SelfTestConfig[1].MSS1);
           setupFile.setValue("MSS2", SelfTestConfig[1].MSS2);
           setupFile.setValue("MSS3", SelfTestConfig[1].MSS3);
           setupFile.setValue("MSS4", SelfTestConfig[1].MSS4);
           setupFile.setValue("MSS5", SelfTestConfig[1].MSS5);

       setupFile.endGroup();


       setupFile.beginGroup("ModBus");

       setupFile.setValue("NumberOfRepeat", Block_Addr.MBRepeat);

       setupFile.endGroup();


       setupFile.beginGroup("SOFT_REGIME");

        setupFile.setValue("CurrentRegime", CurrentSoftRegimeNumber);

       setupFile.endGroup();

}

void MainWindow::ReadRegimSettings(int regim)
{
    QSettings regimSettingsFile(QApplication::applicationDirPath() + "/Config/" + SoftRegimFileName + ".ini", QSettings::IniFormat);

    qDebug() << Q_FUNC_INFO << regimSettingsFile.fileName();

    regimSettingsFile.beginGroup("MSS_FILE");

     MSSFileName[1] = regimSettingsFile.value("Regim1", "").toString();
     MSSFileName[2] = regimSettingsFile.value("Regim2", "").toString();
     MSSFileName[3] = regimSettingsFile.value("Regim3", "").toString();

    regimSettingsFile.endGroup();

    regimSettingsFile.beginGroup("Regim_LK");


     currentRegim[0][3] = regimSettingsFile.value("BDG_LK1", 0).toInt();
     currentRegim[1][3] = regimSettingsFile.value("BDG_LK2", 0).toInt();
     currentRegim[2][3] = regimSettingsFile.value("BDG_LK3", 0).toInt();
     currentRegim[3][3] = regimSettingsFile.value("BDG_LK4", 0).toInt();

     currentRegim[0][4] = regimSettingsFile.value("BDD_LK1", 0).toInt();
     currentRegim[1][4] = regimSettingsFile.value("BDD_LK2", 0).toInt();
     currentRegim[2][4] = regimSettingsFile.value("BDD_LK3", 0).toInt();
     currentRegim[3][4] = regimSettingsFile.value("BDD_LK4", 0).toInt();

     BDG_LK1 -> setEnabled(regimSettingsFile.value("BDG_LK1_EN", true).toBool());
     BDG_LK2 -> setEnabled(regimSettingsFile.value("BDG_LK2_EN", true).toBool());
     BDG_LK3 -> setEnabled(regimSettingsFile.value("BDG_LK3_EN", true).toBool());
     BDG_LK4 -> setEnabled(regimSettingsFile.value("BDG_LK4_EN", true).toBool());

     BDD_LK1 -> setEnabled(regimSettingsFile.value("BDD_LK1_EN", true).toBool());
     BDD_LK2 -> setEnabled(regimSettingsFile.value("BDD_LK2_EN", true).toBool());
     BDD_LK3 -> setEnabled(regimSettingsFile.value("BDD_LK3_EN", true).toBool());
     BDD_LK4 -> setEnabled(regimSettingsFile.value("BDD_LK4_EN", true).toBool());

    regimSettingsFile.endGroup();


}

void MainWindow::WriteRegimSettings(int regim)
{

    QSettings regimSettingsFile(QApplication::applicationDirPath() + "/Config/" + SoftRegimFileName + ".ini", QSettings::IniFormat);

    qDebug() << Q_FUNC_INFO << regimSettingsFile.fileName();

    regimSettingsFile.beginGroup("MSS_FILE");

     regimSettingsFile.setValue("Regim1", MSSFileName[1]);
     regimSettingsFile.setValue("Regim2", MSSFileName[2]);
     regimSettingsFile.setValue("Regim3", MSSFileName[3]);

    regimSettingsFile.endGroup();


    regimSettingsFile.beginGroup("Regim_LK");

     regimSettingsFile.setValue("BDG_LK1", currentRegim[0][3]);
     regimSettingsFile.setValue("BDG_LK2", currentRegim[1][3]);
     regimSettingsFile.setValue("BDG_LK3", currentRegim[2][3]);
     regimSettingsFile.setValue("BDG_LK4", currentRegim[3][3]);

     regimSettingsFile.setValue("BDD_LK1", currentRegim[0][4]);
     regimSettingsFile.setValue("BDD_LK2", currentRegim[1][4]);
     regimSettingsFile.setValue("BDD_LK3", currentRegim[2][4]);
     regimSettingsFile.setValue("BDD_LK4", currentRegim[3][4]);

     regimSettingsFile.setValue("BDG_LK1_EN", BDG_LK1 -> isEnabled());
     regimSettingsFile.setValue("BDG_LK2_EN", BDG_LK2 -> isEnabled());
     regimSettingsFile.setValue("BDG_LK3_EN", BDG_LK3 -> isEnabled());
     regimSettingsFile.setValue("BDG_LK4_EN", BDG_LK4 -> isEnabled());

     regimSettingsFile.setValue("BDD_LK1_EN", BDD_LK1 -> isEnabled());
     regimSettingsFile.setValue("BDD_LK2_EN", BDD_LK2 -> isEnabled());
     regimSettingsFile.setValue("BDD_LK3_EN", BDD_LK3 -> isEnabled());
     regimSettingsFile.setValue("BDD_LK4_EN", BDD_LK4 -> isEnabled());

     regimSettingsFile.endGroup();

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);



    logModel = new QStandardItemModel(1, 2, this);
    logModel -> setHorizontalHeaderLabels(QStringList() << "Type" << "Message");


    logTableView -> setModel(logModel);

    logTableView -> setAlternatingRowColors(true);
    logTableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    logTableView -> setGridStyle(Qt::NoPen);
    logTableView -> verticalHeader() -> hide();
    logTableView -> horizontalHeader() -> setStretchLastSection(true);
  //  logTableView -> resizeRowToContents();
    logTableView -> setWordWrap(false);

    secretMenu = new QMenu("Secret menu");

    QAction *act1 = new QAction(this);

    act1 -> setText(tr("Отключение управления самоконтроля"));
    act1 -> setCheckable(true);
    act1 -> setChecked(true);



    secretMenu -> addAction(act1);

    connect(act1, SIGNAL(triggered(bool)), this, SLOT(slotSelfTestControl(bool)));



    SelfTestControl = false;

    secretMenu -> addAction("Настройка отладки",
                            this,
                            SLOT(slotDebugMenu()),
                            Qt::CTRL + Qt::Key_0);


    secretMenu -> addAction("Ручное управление МСС",
                            this,
                            SLOT(slotManulMSS()),
                            Qt::CTRL + Qt::Key_1);

    secretMenu -> addAction("Настройка файлов МСС",
                            this,
                            SLOT(slotSetMSSFileName()),
                            Qt::CTRL + Qt::Key_2);

    secretMenu -> addAction("Ручное управление ПВД",
                            this,
                            SLOT(slotManualPVD()),
                            Qt::CTRL + Qt::Key_3);

    secretMenu -> addAction("Ручное управление МАГ",
                            this,
                            SLOT(slotManualMAG()),
                            Qt::CTRL + Qt::Key_4);



    connect(gbSecret, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(slotSecretMenuView(QPoint)));


    MBTcp = new ModBusTCP(this);

    connect (MBTcp, SIGNAL(ModBusOK()), this, SLOT(slotModBusOk()));
    connect (MBTcp, SIGNAL(ModBusError(int)), this, SLOT(slotModBusError(int)));

    connect(pbConnect, SIGNAL(clicked()), this, SLOT(slotConnect()));
    connect(pbDisConnect, SIGNAL(clicked()), this, SLOT(slotDisConnect()));
    connect(pbReportSlave, SIGNAL(clicked()), this, SLOT(slotReportSlave()));
    connect(pbSelfTest1, SIGNAL(clicked()), this, SLOT(slotSelfTest1()));
    connect(pbSelfTest2, SIGNAL(clicked()), this, SLOT(slotSelfTest2()));

    connect(pbCheckPVD, SIGNAL(clicked()), this, SLOT(slotCheckPVD()));

    connect(BDD_LK1, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDDLK4(int)));
    connect(BDD_LK2, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDDLK2(int)));
    connect(BDD_LK3, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDDLK3(int)));
    connect(BDD_LK4, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDDLK4(int)));

    connect(BDG_LK1, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDGLK1(int)));
    connect(BDG_LK2, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDGLK2(int)));
    connect(BDG_LK3, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDGLK3(int)));
    connect(BDG_LK4, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeBDGLK4(int)));

    connect(pbLoadMSS, SIGNAL(clicked()),
            this, SLOT(ManualLoadMSS()));



    rsMenuMapper = new QSignalMapper(this);

    QSettings setupFile(QApplication::applicationDirPath() + "/" + QApplication::applicationName() + ".ini", QSettings::IniFormat);
    setupFile.setIniCodec("UTF-8");

    setupFile.beginGroup("SOFT_REGIME");
    QString menuRS;
    int num_regime = 0;

    CurrentSoftRegimeNumber = setupFile.value("CurrentRegime", 0).toInt();

    qDebug() << "CurrentSoftRegim: " << CurrentSoftRegimeNumber;

    menuRS = setupFile.value(QString("Regim%1").arg(num_regime), "").toString();

    while(menuRS != "")
    {
        QAction *act = new QAction(this);

        act -> setText(menuRS);

        act -> setCheckable(true);

        if (CurrentSoftRegimeNumber == num_regime) act -> setChecked(true); else act -> setChecked(false);

        mWorkRegim -> addAction(act);

        connect(act, SIGNAL(triggered()), rsMenuMapper, SLOT(map()));
        rsMenuMapper -> setMapping(act, num_regime);


        num_regime++;
        menuRS = setupFile.value(QString("Regim%1").arg(num_regime), "").toString();

    }


    connect(rsMenuMapper, SIGNAL(mapped(int)), this, SLOT(slotSetRegimeSoft(int)));

    SoftRegimFileName = setupFile.value(QString("Regim%1_file").arg(CurrentSoftRegimeNumber), "").toString();

    setupFile.endGroup();


    ReadSettings();
    ReadRegimSettings(CurrentSoftRegimeNumber);

    MBTcp -> setRepeat(Block_Addr.MBRepeat);

    BDA_LK1 -> setText(regimeName[currentRegim[0][0]]);
    BDA_LK2 -> setText(regimeName[currentRegim[1][0]]);
    BDA_LK3 -> setText(regimeName[currentRegim[2][0]]);
    BDA_LK4 -> setText(regimeName[currentRegim[3][0]]);

    BDB_LK1 -> setText(regimeName[currentRegim[0][1]]);
    BDB_LK2 -> setText(regimeName[currentRegim[1][1]]);
    BDB_LK3 -> setText(regimeName[currentRegim[2][1]]);
    BDB_LK4 -> setText(regimeName[currentRegim[3][1]]);

    BDV_LK1 -> setText(regimeName[currentRegim[0][2]]);
    BDV_LK2 -> setText(regimeName[currentRegim[1][2]]);
    BDV_LK3 -> setText(regimeName[currentRegim[2][2]]);
    BDV_LK4 -> setText(regimeName[currentRegim[3][2]]);


    BDG_LK1 -> setCurrentIndex(currentRegim[0][3]);
    BDG_LK2 -> setCurrentIndex(currentRegim[1][3]);
    BDG_LK3 -> setCurrentIndex(currentRegim[2][3]);
    BDG_LK4 -> setCurrentIndex(currentRegim[3][3]);

    BDD_LK1 -> setCurrentIndex(currentRegim[0][4]);
    BDD_LK2 -> setCurrentIndex(currentRegim[1][4]);
    BDD_LK3 -> setCurrentIndex(currentRegim[2][4]);
    BDD_LK4 -> setCurrentIndex(currentRegim[3][4]);

    //    connect(pbStartCheck, SIGNAL(clicked()),
//            this, SLOT(slotStartCheck()));


    MSSFile[0] = NULL;
    MSSFile[1] = cbMSSRegim1;
    MSSFile[2] = cbMSSRegim2;
    MSSFile[3] = cbMSSRegim3;



}

void MainWindow::setReport(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QStandardItem *ch1 = new QStandardItem(QString(msgType[type]));
    QStandardItem *ch2 = new QStandardItem(msg);



    QList<QStandardItem*> list;

//    list.append(ch1);
//    list.append(ch2);

    list << ch1 << ch2;

    if (logModel != NULL)

        logModel -> insertRow(1, list);
}

void MainWindow::slotStartCheck()
{


    qDebug() << "Запуск проверки";
}


/*
 * Слот проверки ПВД
 *
 */

void MainWindow::slotCheckPVD()
{
    ViewBD view;

    quint8 currRegim[2][4];
    quint8 currDevice = 0;
    quint8 currMSS = 0;

    quint8 RegimForCheck[4] = {1, 1, 1, 1};

    bool check;
    bool BDFirstCheck;


// Загрузка МСС
//    for (int i = 0; i < 3; i++)
//    {
//        slotLoadMSS(i, MSSFile[currentRegim[0][i]] -> currentIndex(), MSSFile[currentRegim[1][i]] -> currentIndex(),
//                       MSSFile[currentRegim[2][i]] -> currentIndex(), MSSFile[currentRegim[3][i]] -> currentIndex());
//    }

//// Установка режимов

//    for (int i = 0; i < 2; i++)
//    {
//        for (int j = 0; j < 4; j++)
//        {
//            if (currentRegim[j][i + 3])
//            {
//                currRegim[i][j] = currentRegim[j][i + 3];
//            } else
//            {
//                currRegim[i][j] = 1;
//            }
//        }
//    }


    if (cbAllCheck -> isChecked())
    {
        currDevice = 0;
    } else
    {
        currDevice = tabWidget->currentIndex();
    }

    qDebug() << " currDevice: " << currDevice;


    currMSS = 0;

    check = true;
    BDFirstCheck = true;

    while (check)
    {



       if (BDFirstCheck) // Если первая проверка текущего БД
       {
          // Заполняем текущий режим проверки либо значением, либо 1 режим при пееборе
          for (int i = 0; i < 4; i++)
          {
              if (currentRegim[i][currDevice] == 0)
                  RegimForCheck[i] = 1;
              else
                  RegimForCheck[i] = currentRegim[i][currDevice];
          }

        } else
          {
            // Иначе увеличиваем режим, если для него выбран перебор
            for (int i = 0; i < 4; i++)
            {
               if (currentRegim[i][currDevice] == 0)
                   RegimForCheck[i]++;
            }
           }



        // Загружаем МСС и устанавливаем режим

        slotLoadMSS(currDevice, RegimForCheck[0], RegimForCheck[1], RegimForCheck[2], RegimForCheck[3]);
        ChangeRegimMSS(currDevice, RegimForCheck[0], RegimForCheck[1], RegimForCheck[2], RegimForCheck[3]);

// !!!!!!!!!!!!! тут должен быть запуск опроса БД и таймер задержки

        // Проверка БД !!!! Надо добавить зацикливание!!!!!!

        for (quint8 currentMSS = 0; currentMSS < 4; currentMSS++) // Пройдемся по всем 4 МСС
        {

            if (!BDFirstCheck && (currentRegim[currentMSS][currDevice])) // Если не первая проверка БД и нет перебора, то мы его уже проверяли
                continue;

//            if (LoadMSSPVD(BDData, currDevice, currentMSS, RegimForCheck[currentMSS], MSSFile[0]->currentIndex()))
//            {
//                qDebug() << "Ошибка чтения БД";
//                check = false;
//                break;
//            }
        }


        // Закончили проверять БД и делаем переход на другой БД или другой режим

        if (check) // Если нет ошибок
        {

            if (BDFirstCheck || currentRegim[0][currDevice]
                    || currentRegim[1][currDevice] || currentRegim[2][currDevice] || currentRegim[3][currDevice])
            {

            }

            if (cbAllCheck->isChecked()) // Если все проверяем
            {
                currDevice++;
                if (currDevice == 5) // Типа все проверили
                {
                    qDebug() << "Ошибок не обнаруженно";
                    check = false;
                }
            }
        }

    }

}

void MainWindow::slotDebugMenu()
{
    qDebug() << "Секретное меню отладки";
}

void MainWindow::slotSelfTestControl(bool tt)
{
    SelfTestControl = !tt;
}

void MainWindow::slotManulMSS()
{
    dManualLoadMSS manWin;

    for(int i = 0; i < 5; i++)
        manWin.slaveAddr[i] = MSS_Addr[i];


    connect(&manWin, SIGNAL(wrMultipleCoils(quint16,quint16,quint16,quint8*)),
            MBTcp, SLOT(WriteMultipleCoils(quint16,quint16,quint16,quint8*)));

    qDebug() << Q_FUNC_INFO;

    manWin.exec();
}

void MainWindow::slotSetMSSFileName()
{

    dMSSFileSet *fsDialog = new dMSSFileSet;

    fsDialog -> exec();

}

void MainWindow::slotManualPVD()
{
    dManualPVD dialog;


    connect(&dialog, SIGNAL(getPVDData(quint16,quint16)), this, SLOT(slotReadPVD(quint16,quint16)));
    connect(this, SIGNAL(ErrorMSSLoad()), &dialog, SLOT(slot_ErrorMSS()));
    connect(this, SIGNAL(MSSData(quint8*)), &dialog, SLOT(slot_ReceivedMSS(quint8*)));

    connect(&dialog, SIGNAL(OnOffPVD(bool,quint8,quint8,quint8,quint8,quint8)),
            this, SLOT(slotOnOffPVD(bool,quint8,quint8,quint8,quint8,quint8)));
    connect(&dialog, SIGNAL(ChangePVDStatus(bool,quint8)),
            this, SLOT(slotChangePVDStatus(bool,quint8)));

    connect(&dialog, SIGNAL(GetTest(bool)), this, SLOT(slotGetPVDTestResult(bool)));
    connect(this, SIGNAL(PVDTestResult(bool,bool,bool,bool,bool,bool)),
            &dialog, SLOT(slot_TestResult(bool,bool,bool,bool,bool,bool)));
    connect(this, SIGNAL(ErrorModBus(quint8)), &dialog, SLOT(slot_ErrorModBus(quint8)));

    dialog.exec();

}

void MainWindow::slotManualMAG()
{

}

void MainWindow::slotSecretMenuView(QPoint pe)
{

    secretMenu -> exec(gbSecret -> mapToGlobal(pe));
}

/*
 *  Слот загрузки имитаторов МСС
 *  num                     - номер блока МСС от 0
 *  ch1, ch2, ch3, ch4      - Номера файлов для загрузки
 *  start                   - байт запуска 0 бит - первый канал
 *
 */
void MainWindow::slotLoadMSS(quint8 num, quint8 ch1, quint8 ch2, quint8 ch3, quint8 ch4)
{


    qDebug() << "Load MSS" << num + 1 << "Ch1:" << ch1 << " Ch2:" << ch2 << " Ch3:" << ch3 << " Ch4:" << ch4;
}

void MainWindow::slotConnect()
{
    qDebug() << "Connect to IP";

    MBTcp -> Connect();
}

void MainWindow::slotDisConnect()
{

}

void MainWindow::slotReportSlave()
{

   BLOCK_STATUS *st;

   QWidget *StatusWindow = new QWidget();

   StatusWindow -> setFixedSize(300, 200);
   QVBoxLayout * layout_sw = new QVBoxLayout();

   StatusWindow -> show();

   StatusWindow->setLayout(layout_sw);

   qDebug() << "sizrof BlockAddr" << sizeof(BlockAddr);

   for (int i = 0; i < sizeof(BlockAddr); i++)
   {



      st = MBTcp -> ReportSlaveID(BlockAddr[i]);

      if (st -> rstatus){



          QLabel *lb = new QLabel();
          lb->setText(QString("Addr: %1 Version %2.%3").arg(BlockAddr[i]).arg(st -> HardVersion).arg(st -> SoftVersion));

          layout_sw -> addWidget(lb);

          QApplication::processEvents();

        qDebug() << "Addr: " << BlockAddr[i] << "Status: " <<  st -> status <<
                    "HardVersion: " << st -> HardVersion << " SoftVersion: " << st -> SoftVersion;

        delete st;
      }
   }
}

void MainWindow::slotSelfTest1()
{
    dSelfTest dialog;

    dialog.setPVD1Test(SelfTestConfig[0].PVD1);
    dialog.setPVD2Test(SelfTestConfig[0].PVD2);
    dialog.setMAG1Test(SelfTestConfig[0].MAG1);
    dialog.setMAG2Test(SelfTestConfig[0].MAG2);

    dialog.setMSS1Test(SelfTestConfig[0].MSS1);
    dialog.setMSS2Test(SelfTestConfig[0].MSS2);
    dialog.setMSS3Test(SelfTestConfig[0].MSS3);
    dialog.setMSS4Test(SelfTestConfig[0].MSS4);
    dialog.setMSS5Test(SelfTestConfig[0].MSS5);


    connect(&dialog, SIGNAL(setPVDStatus(bool,quint8)), this, SLOT(slotChangePVDStatus(bool,quint8)));
    connect(this, SIGNAL(PVDTestResult(bool,bool,bool,bool,bool,bool)),
            &dialog, SLOT(slotPVDTestResult(bool,bool,bool,bool,bool,bool)));
    connect(&dialog, SIGNAL(getPVDTestResult(bool)), this, SLOT(slotGetPVDTestResult(bool)));
    connect(this, SIGNAL(ChangePVDStatusOK()), &dialog, SLOT(slotChangePVDStatusOK()));
    connect(this, SIGNAL(ErrorModBus(quint8)), &dialog, SLOT(slotModBusError(quint8)));


    dialog.setControl(SelfTestControl);


    dialog.exec();
}

void MainWindow::slotSelfTest2()
{
    dSelfTest dialog;

    dialog.setPVD1Test(SelfTestConfig[1].PVD1);
    dialog.setPVD2Test(SelfTestConfig[1].PVD2);
    dialog.setMAG1Test(SelfTestConfig[1].MAG1);
    dialog.setMAG2Test(SelfTestConfig[1].MAG2);

    dialog.setMSS1Test(SelfTestConfig[1].MSS1);
    dialog.setMSS2Test(SelfTestConfig[1].MSS2);
    dialog.setMSS3Test(SelfTestConfig[1].MSS3);
    dialog.setMSS4Test(SelfTestConfig[1].MSS4);
    dialog.setMSS5Test(SelfTestConfig[1].MSS5);

    connect(&dialog, SIGNAL(setPVDStatus(bool,quint8)), this, SLOT(slotChangePVDStatus(bool,quint8)));
    connect(this, SIGNAL(PVDTestResult(bool,bool,bool,bool,bool,bool)),
            &dialog, SLOT(slotPVDTestResult(bool,bool,bool,bool,bool,bool)));
    connect(&dialog, SIGNAL(getPVDTestResult(bool)), this, SLOT(slotGetPVDTestResult(bool)));
    connect(this, SIGNAL(ChangePVDStatusOK()), &dialog, SLOT(slotChangePVDStatusOK()));
    connect(this, SIGNAL(ErrorModBus(quint8)), &dialog, SLOT(slotModBusError(quint8)));


    dialog.setEnabled(SelfTestControl);

    dialog.exec();
}

void MainWindow::changeBDDLK1(int val)
{


    ChangeRegimMSS(1, val, 0, 0, 0);
    setCurrentRegimMSS1BDD(val);



}


void MainWindow::changeBDDLK2(int val)
{

    ChangeRegimMSS(1, 0, val, 0, 0);
    setCurrentRegimMSS2BDD(val);



}

void MainWindow::changeBDDLK3(int val)
{

    ChangeRegimMSS(1, 0, 0, val, 0);
    setCurrentRegimMSS3BDD(val);


}

void MainWindow::changeBDDLK4(int val)
{

    ChangeRegimMSS(1, 0, 0, 0, val);
    setCurrentRegimMSS4BDD(val);



}

void MainWindow::changeBDGLK1(int val)
{


    ChangeRegimMSS(0, val, 0, 0, 0);
    setCurrentRegimMSS1BDG(val);

}

void MainWindow::changeBDGLK2(int val)
{

    ChangeRegimMSS(0, 0, val, 0, 0);
    setCurrentRegimMSS2BDG(val);

}

void MainWindow::changeBDGLK3(int val)
{

    ChangeRegimMSS(0, 0, 0, val, 0);
    setCurrentRegimMSS3BDG(val);


}

void MainWindow::changeBDGLK4(int val)
{

    ChangeRegimMSS(0, 0, 0, 0, val);
    setCurrentRegimMSS4BDG(val);

}

void MainWindow::ManualLoadMSS()
{

    qDebug() << Q_FUNC_INFO;



    MSSLoad(tabWidget -> currentIndex(), currentRegim[0][tabWidget -> currentIndex()],
                                         currentRegim[1][tabWidget -> currentIndex()],
                                         currentRegim[2][tabWidget -> currentIndex()],
                                         currentRegim[3][tabWidget -> currentIndex()]);

}

void MainWindow::slotSetRegimeSoft(int num)
{



    qDebug() << "Ops!!" << num;

    for (int i = 0; i < mWorkRegim->actions().count(); i++)
        mWorkRegim -> actions().at(i) -> setChecked(false);


    mWorkRegim -> actions().at(num) -> setChecked(true);

    this -> setWindowTitle("ТА985М Программа управления и контроля - " + mWorkRegim -> actions().at(num) -> text());


    CurrentSoftRegimeNumber = num;
}

void MainWindow::slotReadPVD(quint16 numBD, quint16 numMSS)
{


    LoadMSSPVD(data, numBD, numMSS);

    if (MBResult == 0)
    {
        emit MSSData(data);
        return;
    } else
    {
        emit ErrorMSSLoad();
    }

}

void MainWindow::slotOnOffPVD(bool osn, quint8 PVD_A, quint8 PVD_B, quint8 PVD_V, quint8 PVD_G, quint8 PVD_D)
{

    //TODO: Добавить адреса разных ПВД и обработку ошибок (Если не прошло, то сигнал с ошибкой иначе сигнал все ОК)

    quint8 data[5];

    data[0] = PVD_A; data[1] = PVD_B; data[2] = PVD_V; data[3] = PVD_G; data[4] = PVD_D;

    if (osn)
    {
        MBTcp -> WriteMultipleCoils(Block_Addr.PVD1, PVD_ONOFF_ADDR, 5, data);
    } else
        MBTcp -> WriteMultipleCoils(Block_Addr.PVD2, PVD_ONOFF_ADDR, 5, data);


}

void MainWindow::slotGetPVDTestResult(bool osn)
{
    quint8 data[6];


    MBResult = 255;

    if (osn)
    {
        MBTcp -> ReadDiscreteInputs(Block_Addr.PVD1, PVD_TEST_RESULT_ADDR_ALL, 6, data);
    } else
    {
        MBTcp -> ReadDiscreteInputs(Block_Addr.PVD2, PVD_TEST_RESULT_ADDR_ALL, 6, data);
    }

    while(MBResult == 255)
        QApplication::processEvents();


    if (MBResult == 0)
    {
        emit PVDTestResult(data[0], data[5], data[4], data[3], data[2], data[1]);
        return;
    } else
    {
        emit ErrorModBus(MBResult);
    }
}

void MainWindow::slotChangePVDStatus(bool osn, quint8 status)
{

    quint8 data[2];


    switch (status) {

    case 0:

        data[0] = 0;
        data[1] = 0;

        break;

    case 1:

        data[0] = 0;
        data[1] = 1;
        break;

    case 2:

        data[0] = 1;
        data[1] = 0;
        break;

    case 3:

        data[0] = 1;
        data[1] = 1;
        break;

    default:

        data[0] = 0;
        data[1] = 0;
        break;
    }
    MBResult = 255;

    if (osn)
    {
        MBTcp -> WriteMultipleCoils(Block_Addr.PVD1, PVD_REGIME_ADDR, 2, data);
    } else
    {
        MBTcp -> WriteMultipleCoils(Block_Addr.PVD2, PVD_REGIME_ADDR, 2, data);
    }



    while(MBResult == 255)
    {
       // qDebug() << MBResult;
        QApplication::processEvents();

    }



    if (MBResult == 0)
    {
        emit ChangePVDStatusOK();
    } else
    {
        emit ErrorModBus(MBResult);
    }
}

void MainWindow::slotModBusError(int err)
{
    qDebug() << Q_FUNC_INFO << err << MBResult;
    MBResult = err;
}

void MainWindow::slotModBusOk()
{
    qDebug() << Q_FUNC_INFO;
    MBResult = 0;
}




