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
    QString filenameSelected = ui->lineEditStart->text();
    ProcessWorker *process = new ProcessWorker(this);

    connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
    process->process(deviceSelected,filenameSelected);

    // if(process->state() == 2) qDebug() << "Running..."; - Check process state!

}

void DialogStart::on_processReadyToRead(const QString &output)
{
 qDebug() << output;
}
