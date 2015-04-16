#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <commands.h>
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

    startNewJob->startJob(deviceSelected);

}
