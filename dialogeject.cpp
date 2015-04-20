#include "dialogeject.h"
#include "ui_dialogeject.h"
#include "ProcessWorker.h"
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

    ProcessWorker *process = new ProcessWorker(this);
    QString deviceSelected = ui->comboBoxEject->currentText();

    connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));

    process->processEject(deviceSelected);



}

void DialogEject::on_processStatusReady(const int state, const QString &sourceDevice)
{
 emit processStateReady(state,sourceDevice);
}
