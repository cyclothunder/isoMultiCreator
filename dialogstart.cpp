#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <ProcessWorker.h>
#include <QDebug>
#include <QString>
#include <QFileDialog>

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
    connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));
    process->process(deviceSelected,filenameSelected);

}

void DialogStart::on_processReadyToRead(const QString &output)
{
 qDebug() << output;
}

void DialogStart::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Filename"), "/", tr("Iso Files (*.iso)"));
    ui->lineEditStart->setText(fileName);

}

void DialogStart::on_processStatusReady(const int state, const QString &sourceDevice)
{
 emit processStateReady(state,sourceDevice);
}
