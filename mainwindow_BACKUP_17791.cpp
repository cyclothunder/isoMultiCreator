#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>
#include <QLayout>
#include <QFileDialog>
#include <QComboBox>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    deviceInfoList = new Misc();
    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());
    ui->listView_Status->setModel(deviceInfoListModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_clicked()
{

    deviceReadyAfterOpened = deviceInfoList->getDevicesReady();
//    if (deviceReadyAfterOpened.isEmpty()) {
//        deviceReadyAfterOpened = deviceInfoList->get_ROdevicesPath();
//    }
    dialog_StartJob = new DialogStart(deviceReadyAfterOpened, this);
    // dialog_StartJob->setDevicesReady(deviceNotReadyAfterOpened);


    connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    connect(dialog_StartJob,SIGNAL(deviceFilename(QString,QString)),this,SLOT(deviceListUpdate(QString,QString)));
    // connect(dialog_eject,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    dialog_StartJob->setWindowTitle("Start Job");

<<<<<<< HEAD
    dialog_StartJob->show();

    timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(deviceListUpdate()));



=======
>>>>>>> 588a4da9b62458e45f776a45134f1e0e24f25749
}

void MainWindow::on_pushButton_Stop_clicked()
{

    deviceNotReady = deviceInfoList->getDevicesNotReady();

    dialog_StopJob = new DialogStop(deviceNotReady, this);
    dialog_StopJob->setWindowTitle("Stop Job");
    dialog_StopJob->show();
}

void MainWindow::on_pushButtonEject_clicked()
{
    deviceReadyAfterOpened = deviceInfoList->getDevicesReady();
    dialog_eject = new DialogEject(deviceReadyAfterOpened, this);
    connect(dialog_eject,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    dialog_eject->setWindowTitle("Eject CD");
    dialog_eject->show();
}

void MainWindow::on_pushButtonRefresh_clicked()
{

    // deviceInfoListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());
    // ui->listView_Status->setModel(deviceInfoListModel);

    QStringListModel *getCurrentDeviceStateListModel;
    getCurrentDeviceStateListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());

    ui->listView_Status->setModel(getCurrentDeviceStateListModel);

}

void MainWindow::on_processStateChange(const int state, const QString &sourceDevice)
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
                break;
            case 1:
                strState = "Starting";
                deviceNotReady << sourceDevice;
                break;
            case 2:
                strState = "Running";
                deviceNotReady << sourceDevice;
                break;
            }


            temp.replace(3,"State: " + strState );
            deviceInfoListModel->setData(deviceInfoListModel->index(i),temp.join("\n"));


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
        timer->start(1000);
    }

//    devListUpdated = deviceInfoListModel;
//    devListUpdated(deviceInfoListModelStateUpdated);
    // emit deviceInfoListModel;
}

//QStringListModel devListUpdated(QStringListModel parentDevList){
//    QStringListModel devListUp = parentDevList;

//    return devListUp;    

}

void MainWindow::deviceListUpdate(QString parentSource, QString parentDestination)

{

<<<<<<< HEAD
    //QString sourceDevice = dialog_StartJob->get_deviceSelectedGeneral();
    QString sourceDevice = onStateChangeToRunning;

    QFile filenameSelectedStart(dialog_StartJob->get_filenameSelectedGeneral());
=======
    QString source = parentSource;
    QString destination = parentDestination;

//    QString sourceDevice = dialog_StartJob->get_deviceSelectedGeneral();

    QFile filenameSelectedStart(destination);
>>>>>>> 588a4da9b62458e45f776a45134f1e0e24f25749
    qint64 fileSize = filenameSelectedStart.size();
    QString fileSizeString = QString::number(fileSize/1024/1024); // Converting to MB;

    // QStringListModel *deviceInfoListModelProgress = new QStringListModel(deviceInfoList->getDevicesCurrentState());
    deviceInfoListModel = new QStringListModel(deviceInfoList->getDevicesCurrentState());

    for (int i = 0; i < deviceInfoListModel->rowCount();i++) {
        QStringList temp = deviceInfoListModel->index(i).data().toString().split("\n");

        if (temp.at(0).contains(source)) {
            temp.replace(3, "Running - " + fileSizeString + " Bytes");
        }

        deviceInfoListModel->setData(deviceInfoListModel->index(i),temp.join("\n"));
    }

<<<<<<< HEAD
    if(sourceDevice != "Running")
    timer->stop();
=======
    ui->listView_Status->setModel(deviceInfoListModelProgress);
>>>>>>> 588a4da9b62458e45f776a45134f1e0e24f25749

    if(fileSizeString == fileSizeString) timer->stop();

}

