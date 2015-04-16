#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringListModel>
#include <QLayout>
#include <Qlabel>
#include <QComboBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    deviceInfoList = new Misc();
    deviceInfoListModel = new QStringListModel(deviceInfoList->get_ROdevicesInfo());

    ui->listView_Status->setModel(deviceInfoListModel);

//    QGridLayout *myLayout = new QGridLayout;
//    QLabel *statusLabel_Device = new QLabel("Device: ");

//    myLayout->addWidget(statusLabel_Device,0,0);

//    ui->status_WidgetBox->setLayout(myLayout);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Start_clicked()
{
    dialog_StartJob = new DialogMainButtons(this);
    dialog_StartJob->setWindowTitle("Start Job");

    QLabel *selectDevice_Text = new QLabel("Select Device");
    QComboBox *combobox_deviceList = new QComboBox;
    QGridLayout *layoutStartDialog = new QGridLayout;

    layoutStartDialog->addWidget(combobox_deviceList,1,0);
    layoutStartDialog->addWidget(selectDevice_Text,0,0);
    dialog_StartJob->setLayout(layoutStartDialog);


    dialog_StartJob->show();
}

void MainWindow::on_pushButton_Stop_clicked()
{
    dialog_StopJob = new DialogMainButtons(this);
    dialog_StopJob->setWindowTitle("Stop Job");
    dialog_StopJob->show();
}

void MainWindow::on_pushButtonEject_clicked()
{
    dialog_eject = new DialogMainButtons(this);
    dialog_eject->setWindowTitle("Eject CD");
    dialog_eject->show();
}
