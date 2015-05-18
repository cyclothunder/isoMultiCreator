#include "dialogstopconfirm.h"
#include "ui_dialogstopconfirm.h"

DialogStopConfirm::DialogStopConfirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStopConfirm)
{
    ui->setupUi(this);

}

DialogStopConfirm::~DialogStopConfirm()
{
    delete ui;
}
