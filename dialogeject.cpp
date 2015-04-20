#include "dialogeject.h"
#include "ui_dialogeject.h"

DialogEject::DialogEject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEject)
{
    ui->setupUi(this);

    deviceListPathOnly = new Misc();
    deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    // ui->comboBoxEject->setModel(deviceListPathOnlyModel);

}

DialogEject::~DialogEject()
{
    delete ui;
}

void DialogEject::on_buttonBox_accepted()
{
    dialog_StopConfirm = new DialogStopConfirm(this);
    dialog_StopConfirm->setWindowTitle("WARNING");
    dialog_StopConfirm->show();
}
