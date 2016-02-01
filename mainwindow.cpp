#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QLayout>
#include <QFileDialog>
#include <QComboBox>
#include <QDebug>
#include <QStorageInfo>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);        

    deviceInfoList = new Misc();
    structSize = 0;

    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());
    ui->listView_Status->setModel(deviceInfoListModel);

    hddListCount = 0;
    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
           if (deviceList.isValid() && deviceList.isReady()) {
               if (!deviceList.isReadOnly()) {
                   hddListCount++;
               }
           }
    }

        hddList = new hardDisk[hddListCount];
        hddList = deviceInfoList->get_HardDrivesInfo();


        //*hddList = deviceInfoList->get_HardDrivesInfo();

        for (int x = 0; x < hddListCount; x++) {
            qDebug() << "------ 2nd Part ------";
            qDebug() << "Label -" << hddList[x].label;
            qDebug() << "Device -" << hddList[x].device;
            qDebug() << "Total -" << hddList[x].totalBytes << "Gb";
            qDebug() << "Free -" << hddList[x].freeBytes << "Gb";
            qDebug() << "State -" << hddList[x].state;
            qDebug() << "------ empty line ------";

        }

    for (int var = 0; var < hddListCount; var++) {
        QLabel *hddLabelName = new QLabel(this);
        hddLabelName->setText(hddList[var].label + "\n" +
                              "Free: " + hddList[var].freeBytes + " Gb\n" +
                              hddList[var].state + "\n");

        ui->hddLayout->addWidget(hddLabelName);

    }

    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(deviceListUpdate()));
        timer->start(5000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_clicked()
{

    deviceReadyAfterOpened = deviceInfoList->getDevicesReady();

    dialog_StartJob = new DialogStart(deviceReadyAfterOpened, this);

    // dialog_StartJob->setDevicesReady(deviceNotReadyAfterOpened);

    connect(dialog_StartJob,SIGNAL(processStateReady(int,QString,QString, qint64, QString)),this,SLOT(on_processStateChange(int,QString,QString, qint64, QString)));
    connect(dialog_StartJob,SIGNAL(processReadyToReadOutput(QString)),this,SLOT(readOutput(QString)));
    // connect(dialog_eject,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    dialog_StartJob->setWindowTitle("Start Job");

    dialog_StartJob->show();


    // QMap<QString, qint64> allDevicesProcessID[tempDeviceSelected] = tempProcessID;

//    timer = new QTimer(this);
//        connect(timer, SIGNAL(timeout()), this, SLOT(deviceListUpdate()));

}

void MainWindow::on_pushButton_Stop_clicked()
{

    deviceNotReady = deviceInfoList->getDevicesNotReady();
    QMap<QString, qint64> currentDevPids = deviceInfoList->getMapDevPid();

//    dialog_StopJob = new DialogStop(deviceNotReady, &currentDevPids, this);
    dialog_StopJob = new DialogStop(deviceNotReady, devPidList, this);

    dialog_StopJob->setWindowTitle("Stop Job");
    dialog_StopJob->show();
}

void MainWindow::on_pushButtonEject_clicked()
{


    deviceReadyAfterOpened = deviceInfoList->getDevicesReady();

    dialog_eject = new DialogEject(deviceReadyAfterOpened, this);
    // connect(dialog_eject,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    dialog_eject->setWindowTitle("Eject CD");
    dialog_eject->show();
}

/*
void MainWindow::on_pushButtonRefresh_clicked()
{

    // deviceInfoListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());
    // ui->listView_Status->setModel(deviceInfoListModel);

    QStringListModel *getCurrentDeviceStateListModel;
    getCurrentDeviceStateListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());

    ui->listView_Status->setModel(getCurrentDeviceStateListModel);

}

*/

void MainWindow::on_processStateChange(const int state, const QString &sourceDevice, const QString &destination, const qint64 &pid, const QString destinationStorage)
{

    qDebug() << "State of device" << sourceDevice << "is" << state;
    deviceInfoListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());
    for (int i = 0; i < deviceInfoListModel->rowCount();i++) {
        QStringList temp = deviceInfoListModel->index(i).data().toString().split("\n");
        QString strState = "Unknown";
        if (temp.at(0).contains("Device: " + sourceDevice)) {
            switch (state) {
            case 0:
                strState = "Ready";
                deviceReady << sourceDevice;
                hddState << destinationStorage;
                break;
            case 1:
                strState = "Starting";
                deviceNotReady << sourceDevice;
                hddState << destinationStorage;
                break;
            case 2:
                strState = "Running";
                deviceNotReady << sourceDevice;
                hddState << destinationStorage;
                break;
            }


            if(temp.at(3).contains("Running") == false)
                temp.replace(3,"State: " + strState );

            deviceInfoListModel->setData(deviceInfoListModel->index(i),temp.join("\n"));  

        }
    }

    ui->listView_Status->setModel(deviceInfoListModel);
    // QStringList deviceCurrentList = deviceInfoListModel->data.toStringList();
    int myRowCount = deviceInfoListModel->rowCount();
    QStringList temp2;

    for (int i = 0; i < deviceInfoListModel->rowCount();i++) {
        temp2 << deviceInfoListModel->index(i).data().toString();
    }

    deviceReadyAfterOpened = deviceReady;
    deviceNotReadyAfterOpened = deviceNotReady;
    deviceInfoList->setDevicesCurrentState(temp2);
    deviceInfoList->setDevicesReady(deviceReady);
    deviceInfoList->setDevicesNotReady(deviceNotReady);

    if(state == 2)
    {
        onStateChangeToRunning = sourceDevice;
        filenameMap[sourceDevice] = destination;
        devPidList[sourceDevice] = pid;
    }
    else{
        if(state == 0){

            filenameMap.remove(sourceDevice);
            devPidList.remove(sourceDevice);

            int devicesRunning = 0;

            deviceInfoListModel2 = new QStringListModel(temp2);

            for (int i = 0; i < deviceInfoListModel2->rowCount();i++) {
                QStringList temp = deviceInfoListModel2->index(i).data().toString().split("\n");

                if (temp.at(3).contains("Running")) {
                    devicesRunning += 1;
                }
                else devicesRunning += 0;

                deviceInfoListModel2->setData(deviceInfoListModel2->index(i),temp.join("\n"));
            }

         }
     }

    qDebug() << "-----> destinationstorage: " << destinationStorage;

    for(int hddcount = 0; hddcount < hddListCount; hddcount++){
        if(hddList[hddcount].label == destinationStorage){
            if(hddList[hddcount].state == "Ready" ) hddList[hddcount].label = "Busy";
            else hddList[hddcount].label = "Ready";
        }
    }

}   

void MainWindow::deviceListUpdate()
{

    QMap<QString, QString> temp_filenameMap = filenameMap;
    QMapIterator<QString, QString> iter_filenameMap(temp_filenameMap);
    QStringList temp2;

    deviceInfoListModel2 = new QStringListModel(deviceInfoList->getDevicesCurrentState());

    while(iter_filenameMap.hasNext()){

        iter_filenameMap.next();
        QString sourceDevice = iter_filenameMap.key();
        QString filename = iter_filenameMap.value();
        QFile filenameSelectedStart(filename);
        qint64 fileSize = filenameSelectedStart.size();
        QString fileSizeString = QString::number(fileSize/1024/1024); // Converting to MB;




        for (int i = 0; i < deviceInfoListModel2->rowCount();i++) {

            QStringList temp = deviceInfoListModel2->index(i).data().toString().split("\n");


            if (temp.at(0).contains(sourceDevice)) {
                temp.replace(3, "State: Running - " + fileSizeString + " Mb - " + filename);

            }

            deviceInfoListModel2->setData(deviceInfoListModel2->index(i),temp.join("\n"));

        }

    }

    for (int i = 0; i < deviceInfoListModel2->rowCount();i++) {
        temp2 << deviceInfoListModel2->index(i).data().toString();
    }

    ui->listView_Status->setModel(deviceInfoListModel2);
    deviceInfoList->setDevicesCurrentState(temp2);


    hddList = deviceInfoList->get_HardDrivesInfo();
    hddListCount = 0;
    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
           if (deviceList.isValid() && deviceList.isReady()) {
               if (!deviceList.isReadOnly()) {
                   hddListCount++;
               }
           }
    }

    QLayoutItem *child;
    while( (child = ui->hddLayout->takeAt(0)) != 0) {
        delete child->widget();
        delete child;
    }

    for (int var = 0; var < hddListCount; var++) {

        QLabel *hddLabelName = new QLabel(this);
        hddLabelName->setText(hddList[var].label + "\n" +
                              "Free: " + hddList[var].freeBytes + " Gb\n" +
                              hddList[var].state + "\n");

        ui->hddLayout->addWidget(hddLabelName);

    }


}

void MainWindow::readOutput(QString output){
    qDebug() << "ALL OUTPUT: " << output;
}

