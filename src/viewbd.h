#ifndef VIEWBD_H
#define VIEWBD_H

#include "ui_viewbd.h"

class ViewBD : public QDialog, private Ui::ViewBD
{
    Q_OBJECT

public:
    explicit ViewBD(QWidget *parent = 0);
};

#endif // VIEWBD_H
