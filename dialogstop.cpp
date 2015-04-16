#include "dialogstop.h"
#include "ui_dialogstop.h"

DialogStop::DialogStop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStop)
{
    ui->setupUi(this);

    deviceListPathOnly = new Misc();
    deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    ui->comboBoxStop->setModel(deviceListPathOnlyModel);

}

DialogStop::~DialogStop()
{
    delete ui;
}

void DialogStop::on_buttonBoxStop_accepted()
{
    dialog_StopConfirm = new DialogStopConfirm(this);
    dialog_StopConfirm->setWindowTitle("WARNING");
    dialog_StopConfirm->show();
}
