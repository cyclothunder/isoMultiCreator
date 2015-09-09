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

    deviceListPathOnly = new Misc;

    // deviceListPathOnlyModel = new QStringListModel(deviceListPathOnly->get_ROdevicesPath());
    // ui->comboBoxEject->setModel(deviceListPathOnlyModel);

    // connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));


    QStringList newlist = deviceListPathOnly->getDevicesReady();

    if(newlist.isEmpty()){
        ui->label_eject->setStyleSheet("QLabel { color : red; }");
        ui->label_eject->setText("All devices running");
    }else{

        QStringListModel *newListModel = new QStringListModel(devList);
        ui->comboBoxEject->setModel(newListModel);
        devReadyVolumes = deviceListPathOnly->getDevicesCurrentState();

        for (int i = 0; i < devReadyVolumes.size();i++) {

            if (devReadyVolumes.at(i).contains(ui->comboBoxEject->currentText())) {
                QStringList temp1 = devReadyVolumes.at(i).split("\n");
                QString temp2 = temp1.at(1);

                // temp2.replace("Label: ", "");

                ui->label_eject->setText(temp2);

            }
        }

    }
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

    connect(process,SIGNAL(stateReady(int,QString,QString,qint64)),this,SLOT(on_processStatusReady(int,QString)));

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

void DialogEject::on_comboBoxEject_currentTextChanged(const QString &arg1)
{
    for (int i = 0; i < devReadyVolumes.size();i++) {

        if (devReadyVolumes.at(i).contains(arg1)) {
            QStringList temp1 = devReadyVolumes.at(i).split("\n");
            QString temp2 = temp1.at(1);
            // temp2.replace("Label: ", "");
            ui->label_eject->setText(temp2);
        }
    }
}
