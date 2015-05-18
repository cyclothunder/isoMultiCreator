#include "dialogstop.h"
#include "ui_dialogstop.h"

DialogStop::DialogStop(const QStringList devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStop)
{
    ui->setupUi(this);

    QStringListModel *newList = new QStringListModel(devList);
    ui->comboBoxStop->setModel(newList);

    if (ui->comboBoxStop->currentText() == "") {
        ui->label_allReady->setStyleSheet("QLabel { color : red; }");
        ui->label_allReady->setVisible(true);
    }else ui->label_allReady->setVisible(false);

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
