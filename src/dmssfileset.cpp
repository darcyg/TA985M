#include "dmssfileset.h"

dMSSFileSet::dMSSFileSet(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);


    for(int i = 0; i < 4; i++)
        MSSFile[i] = "";

    selButton[0] = NULL; selButton[1] = pbSelect1; selButton[2] = pbSelect2; selButton[3] = pbSelect3;

    pbMapper = new QSignalMapper(this);

    connect(pbSelect1, SIGNAL(clicked()), pbMapper, SLOT(map()));
    pbMapper -> setMapping(pbSelect1, 1);

    connect(pbSelect2, SIGNAL(clicked()), pbMapper, SLOT(map()));
    pbMapper -> setMapping(pbSelect2, 2);

    connect(pbSelect3, SIGNAL(clicked()), pbMapper, SLOT(map()));
    pbMapper -> setMapping(pbSelect3, 3);

    connect(pbMapper, SIGNAL(mapped(int)), this, SLOT(slotSelectFile(int)));

}

void dMSSFileSet::slotSelectFile(int RegimNum)
{
    qDebug() << Q_FUNC_INFO << RegimNum;
}
