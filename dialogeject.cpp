#include "dialogeject.h"
#include "ui_dialogeject.h"
#include "ProcessWorker.h"
#include "dialogstart.h"
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QString>


DialogEject::DialogEject(const QStringList devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogEject)
{
    ui->setupUi(this);

    // deviceListPathOnly = new Misc();
    // deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    // ui->comboBoxEject->setModel(deviceListPathOnlyModel);

    // connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));


    QStringListModel *newList = new QStringListModel(devList);
    ui->comboBoxEject->setModel(newList);

    if (ui->comboBoxEject->currentText() == "") {
        ui->label_eject->setStyleSheet("QLabel { color : red; }");
        ui->label_eject->setVisible(true);
    }else ui->label_eject->setVisible(false);


}

DialogEject::~DialogEject()
{
    delete ui;
}

void DialogEject::on_buttonBox_accepted()
{

    ProcessWorker *process = new ProcessWorker(this);
    QString deviceSelected = ui->comboBoxEject->currentText();

    // connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));

    connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));

    process->processEject(deviceSelected);
//    deviceInfoList = new Misc();

//    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());

//    QString item;
//    QStringList deviceList;

//    for (int i = 0; i < deviceInfoListModel->rowCount();i++) {
//        QStringList temp = deviceInfoListModel->index(i).data().toString().split("\n");

//        for (int x = 0; x < temp.count(); x++) {

//            if (temp.at(i).contains("Ready")) {

//                item.append(temp.at(i));
//                deviceList << item;
//            }

//            deviceInfoListModel->setData(deviceInfoListModel->index(i),temp.join("\n"));


//        }

//        deviceInfoListModel = new QStringListModel(deviceList);

//        ui->comboBoxEject->setModel(deviceInfoListModel);



//    }
}

//void DialogEject::on_processStatusReady(const int state, const QString &sourceDevice)
//{
// emit processStateReady(state,sourceDevice);
//}

void DialogEject::on_processStatusReady(const int state, const QString &sourceDevice)
{
 emit processStateReady(state,sourceDevice);
}
