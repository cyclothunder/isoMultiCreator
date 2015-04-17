#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <ProcessWorker.h>
#include <QDebug>
#include <QString>

DialogStart::DialogStart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);

    deviceListPathOnly = new Misc();
    deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    ui->comboBoxStart->setModel(deviceListPathOnlyModel);

}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_dialogButtonBoxStart_accepted()
{

    QString deviceSelected = ui->comboBoxStart->currentText();
    ProcessWorker *process = new ProcessWorker(this);

    connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
    process->process(deviceSelected,"/tmp/test.iso");

    if(process->state() == 2) qDebug() << "Running...";

}

void DialogStart::on_processReadyToRead(QString output)
{
 qDebug() << output;
}
