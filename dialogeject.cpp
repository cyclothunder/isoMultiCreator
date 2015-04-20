#include "dialogeject.h"
#include "ui_dialogeject.h"
#include <QProcess>
#include <QStringList>

DialogEject::DialogEject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEject)
{
    ui->setupUi(this);

    deviceListPathOnly = new Misc();
    deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    ui->comboBoxEject->setModel(deviceListPathOnlyModel);


}

DialogEject::~DialogEject()
{
    delete ui;
}

void DialogEject::on_buttonBox_accepted()
{

    QStringList args;

    args << ui->comboBoxEject->currentText();
    QProcess::execute("eject",args);

}
