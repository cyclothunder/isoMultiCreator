#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>
#include <QLayout>
// #include <Qlabel>
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
