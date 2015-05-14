#include "dialogstop.h"
#include "ui_dialogstop.h"

DialogStop::DialogStop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStop)
{
    ui->setupUi(this);

    deviceListPathOnly = new Misc();
    deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->getDevicesNotReady());
    ui->comboBoxStop->setModel(deviceListPathOnlyModel);
    ui->label_allReady->setVisible(false);

}

DialogStop::~DialogStop()
{
    delete ui;
}

void DialogStop::on_buttonBoxStop_accepted()
{

    if (ui->comboBoxStop->currentText() != "") {
        dialog_StopConfirm = new DialogStopConfirm(this);
        dialog_StopConfirm->setWindowTitle("WARNING");
        dialog_StopConfirm->show();
    } else {
        ui->label_allReady->setStyleSheet("QLabel { color : red; }");
        ui->label_allReady->setVisible(true);
    }
}
