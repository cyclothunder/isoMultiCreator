#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>
#include <QLayout>
#include <QFileDialog>
#include <QComboBox>



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
    dialog_StartJob = new DialogStart(this);
    connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    connect(dialog_eject,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)));
    dialog_StartJob->setWindowTitle("Start Job");
    dialog_StartJob->show();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    dialog_StopJob = new DialogStop(this);
    dialog_StopJob->setWindowTitle("Stop Job");
    dialog_StopJob->show();
}

void MainWindow::on_pushButtonEject_clicked()
{
    dialog_eject = new DialogEject(this);
    dialog_eject->setWindowTitle("Eject CD");
    dialog_eject->show();
}

void MainWindow::on_pushButtonRefresh_clicked()
{

    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());
    ui->listView_Status->setModel(deviceInfoListModel);



}

void MainWindow::on_processStateChange(const int state, const QString &sourceDevice)
{


    qDebug() << "State of device" << sourceDevice << "is" << state;
    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());
    for (int i = 0; i < deviceInfoListModel->rowCount();i++) {
        QStringList temp = deviceInfoListModel->index(i).data().toString().split("\n");
        QString strState = "Unknown";
        if (temp.at(0).contains("Device: " + sourceDevice)) {
            switch (state) {
            case 0:
                strState = "Ready";
                break;
            case 1:
                strState = "Starting";
                break;
            case 2:
                strState = "Running";
                break;
            }


            temp.replace(3,"State: " + strState );
            deviceInfoListModel->setData(deviceInfoListModel->index(i),temp.join("\n"));
        }

    }

    ui->listView_Status->setModel(deviceInfoListModel);

}
