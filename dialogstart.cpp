#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <ProcessWorker.h>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QSysInfo>

DialogStart::DialogStart(const QStringList devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);
    QStringListModel *newList = new QStringListModel(devList);

    ui->comboBoxStart->setModel(newList);


    // connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)))

    // Misc getDevices;

    ui->label_filename->setVisible(false);
}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_processReadyToRead(const QString &output)
{
 emit processReadyToReadOutput(output);
}

void DialogStart::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Filename"), "/", tr("Iso Files (*.iso)"));
    ui->lineEditStart->setText(fileName);
    ui->label_filename->setVisible(false);

}

void DialogStart::on_processStatusReady(const int state, const QString &sourceDevice)
{
 emit processStateReady(state,sourceDevice);
}


void DialogStart::on_buttonBox_accepted()
{
    QString deviceSelected;
    QSysInfo wichOS;
    QString filenameSelected = ui->lineEditStart->text();




    if(wichOS.kernelType() == "darwin"){
        Misc volumeInfo;
        QString volumeSelected;
        volumeSelected = volumeInfo.get_OSXvolumes(ui->comboBoxStart->currentText());

        deviceSelected = ui->comboBoxStart->currentText();
        set_deviceSelectedGeneral(deviceSelected);
        set_filenameSelectedGeneral(filenameSelected);


        if (filenameSelected != "") {

            ProcessWorker *process = new ProcessWorker(this);

            connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
            connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));

            process->process(deviceSelected,filenameSelected,volumeSelected);
            this->close();

        } else {
            ui->label_filename->setStyleSheet("QLabel { color : red; }");
            ui->label_filename->setVisible(true);
        }

    }else{
        deviceSelected = ui->comboBoxStart->currentText();
        set_deviceSelectedGeneral(deviceSelected);
        set_filenameSelectedGeneral(filenameSelected);



        if (filenameSelected != "") {

            ProcessWorker *process = new ProcessWorker(this);

            connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
            connect(process,SIGNAL(stateReady(int,QString)),this,SLOT(on_processStatusReady(int,QString)));

            process->process(deviceSelected,filenameSelected);
            this->close();

        } else {
            ui->label_filename->setStyleSheet("QLabel { color : red; }");
            ui->label_filename->setVisible(true);
        }

    }






}

void DialogStart::on_buttonBox_rejected()
{
    this->close();
}

void DialogStart::setDevicesReady(const QStringList &parentList){
     startDevicesReady = parentList;
     QStringListModel *devReadyOnly = new QStringListModel(parentList);

     ui->comboBoxStart->setModel(devReadyOnly);

}

QStringList DialogStart::getDevicesReady(){
//    if (startDevicesReady.isEmpty()) {
//        deviceListPathOnly = new Misc;
//        startDevicesReady = deviceListPathOnly->getDevicesReady();
//    }

    return startDevicesReady;
}

void DialogStart::set_deviceSelectedGeneral(QString &sourceDevice)
{
    deviceSelectedGeneral = sourceDevice;

}

void DialogStart::set_filenameSelectedGeneral(QString &filename)
{
    filenameSelectedGeneral = filename;


}

QString DialogStart::get_deviceSelectedGeneral(){
    return deviceSelectedGeneral;
}

QString DialogStart::get_filenameSelectedGeneral(){
    return filenameSelectedGeneral;
}
