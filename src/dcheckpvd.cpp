#include "dcheckpvd.h"

void dCheckPVD::CreateStateMashine()
{


    mashine = new QStateMachine;

    TopState = new QState;


    sWaitStart = new QState(TopState);
    sStart = new QState(TopState);
    sLoadMSS = new QState(TopState);


    FinalState = new QFinalState;


    sWaitStart -> addTransition(pbStart, SIGNAL(clicked()), sStart);


    sWaitStart -> assignProperty(label, "text", "WaitStart");
    sWaitStart -> assignProperty(pbStart, "enabled", true);
    sWaitStart -> assignProperty(pbStop, "enabled", false);


    sStart -> assignProperty(label, "text", "Start");
    sStart -> assignProperty(pbStart, "enabled", false);
    sStart -> assignProperty(pbStop, "enabled", true);

    sStart -> assignProperty(this, "currBD_Number", 1);




    connect(sStart, SIGNAL(entered()), this, SLOT(slotTest1()));

    connect(FinalState, SIGNAL(entered()), this, SLOT(slotStopChecking()));


    TopState -> addTransition(pbStop, SIGNAL(clicked()), FinalState);

    mashine -> addState(TopState);
    mashine -> addState(FinalState);

    TopState -> setInitialState(sWaitStart);
    mashine -> setInitialState(TopState);


}

dCheckPVD::dCheckPVD(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    CreateStateMashine();

    timer = new QTimer;

    connect(timer, SIGNAL(timeout()), this, SLOT(timeOut()));

    timer -> start(500);

    mashine -> start();
}

void dCheckPVD::slotTest1()
{
    QMessageBox::warning(this, "Test", "Opana!!!!", QMessageBox::Ok);
}

void dCheckPVD::timeOut()
{
    //if (!mashine -> isRunning()) label -> setText("Stop"); else label -> setText("Start");
}

void dCheckPVD::slotStopChecking()
{

    QMessageBox::warning(this, "Stop", "Stop checking", QMessageBox::Ok);

    pbStart -> setEnabled(true);
    pbStop -> setDisabled(true);
    pbClose -> setEnabled(true);


}

void dCheckPVD::setCurrBD_Number(quint8 val)
{

    qDebug() << Q_FUNC_INFO << val;

}

void dCheckPVD::setLoadMSS(bool flag)
{
    if (flag)
    {

    }

}
