#include "dcheckpvd.h"

void dCheckPVD::CreateStateMashine()
{


    mashine = new QStateMachine;

    TopState = new QState;


    WaitStart = new QState(TopState);
    Start = new QState(TopState);
    LoadMSS = new QState(TopState);


    FinalState = new QFinalState;


    WaitStart -> addTransition(pbStart, SIGNAL(clicked()), Start);


    WaitStart -> assignProperty(label, "text", "WaitStart");
    WaitStart -> assignProperty(pbStart, "enabled", true);
    WaitStart -> assignProperty(pbStop, "enabled", false);


    Start -> assignProperty(label, "text", "Start");
    Start -> assignProperty(pbStart, "enabled", false);
    Start -> assignProperty(pbStop, "enabled", true);




    connect(Start, SIGNAL(entered()), this, SLOT(slotTest1()));

    TopState -> addTransition(pbStop, SIGNAL(clicked()), FinalState);

    mashine -> addState(TopState);
    mashine -> addState(FinalState);

    TopState -> setInitialState(WaitStart);
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
