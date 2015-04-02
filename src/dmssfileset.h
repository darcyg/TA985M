#ifndef DMSSFILESET_H
#define DMSSFILESET_H

#include "ui_dmssfileset.h"


#include <QDebug>
#include <QPushButton>
#include <QString>
#include <QSignalMapper>

class dMSSFileSet : public QDialog, private Ui::dMSSFileSet
{
    Q_OBJECT

private:

    QString MSSFile[4];                 // Имена файлоф для режимов, режимы 1-3, 0 - не спользуется
    QPushButton *selButton[4];          // Массив кнопок выбора файлов,  0 - неиспользуется


    QSignalMapper *pbMapper;



public:
    explicit dMSSFileSet(QWidget *parent = 0);


public slots:

    void slotSelectFile(int RegimNum);      // Слот нажатия на кнопку выбора файла
};

#endif // DMSSFILESET_H
