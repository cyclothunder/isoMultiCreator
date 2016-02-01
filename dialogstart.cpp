#include "dialogstart.h"
#include "ui_dialogstart.h"
#include <ProcessWorker.h>
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QSysInfo>
#include <QStorageInfo>

DialogStart::DialogStart(const QStringList devList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStart)
{
    ui->setupUi(this);    


    deviceListPathOnly = new Misc;
    QStringList devReadyStart = deviceListPathOnly->getDevicesReady();
    devReadyVolumes = deviceListPathOnly->getDevicesCurrentState();

//    QStringListModel *newList = new QStringListModel(devReadyStart);
    QStringListModel *newList = new QStringListModel(devList);


    // connect(dialog_StartJob,SIGNAL(processStateReady(int,QString)),this,SLOT(on_processStateChange(int,QString)))

    // Misc getDevices;

    ui->comboBoxStart->setModel(newList);
    ui->label_filename->setText("");

    for (int i = 0; i < devReadyVolumes.size();i++) {

        if (devReadyVolumes.at(i).contains(ui->comboBoxStart->currentText())) {
            QStringList temp1 = devReadyVolumes.at(i).split("\n");
            QString temp2 = temp1.at(1);
            temp2.replace("Label: ", "");
            ui->label_VolumeName->setText(temp2);
        }
    }


//    ui->label_filename->setVisible(false);

}

DialogStart::~DialogStart()
{
    delete ui;
}

void DialogStart::on_processReadyToRead(const QString &output)
{
    qDebug() << "El Output: " << output;
 emit processReadyToReadOutput(output);
}

void DialogStart::on_pushButton_clicked()
{

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Filename"), "/", tr("Iso Files (*.iso)"));
    ui->lineEditStart->setText(fileName);
    ui->label_filename->setVisible(false);

    fileName.truncate(fileName.lastIndexOf("/")+1);
    qDebug() << "filename: " << fileName;

    QStorageInfo storageSelected(fileName);

    if (storageSelected.isValid() && storageSelected.isReady()) {

        destinationStorage = storageSelected.displayName();
        qDebug() << "stor start dialog: " << destinationStorage;
    }
    else qDebug() << "Invalid Drive";


}

void DialogStart::on_processStatusReady(const int state, const QString &sourceDevice, const QString &destination, const qint64 &pid, const QString destinationStorage)
{
 emit processStateReady(state,sourceDevice,destination, pid, destinationStorage);
}

//void DialogStart::on_send_SourceDestination(QString source, QString destination)
//{
//    emit send_SourceDestination(source, destination);

void DialogStart::on_buttonBox_accepted()
{

    QSysInfo wichOS;
    QString filenameSelected = ui->lineEditStart->text();
    filenameSelected = filenameSelected.trimmed();

    if(wichOS.kernelType() == "darwin"){
        Misc volumeInfo;
        QString volumeSelected;
        volumeSelected = volumeInfo.get_OSXvolumes(ui->comboBoxStart->currentText());

        deviceSelected = ui->comboBoxStart->currentText();
        set_deviceSelectedGeneral(deviceSelected);
        set_filenameSelectedGeneral(filenameSelected);


        if (filenameSelected != "") {

            ProcessWorker *process = new ProcessWorker(this);
            qint64 pid;

            connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
            connect(process,SIGNAL(stateReady(int,QString,QString, qint64, QString)),this,SLOT(on_processStatusReady(int,QString,QString, qint64, QString)));

            process->process(deviceSelected,filenameSelected,volumeSelected,destinationStorage);
            pid = process->processId();

            setProcessID(pid);

            this->close();

        } else {
            ui->label_filename->setStyleSheet("QLabel { color : red; }");
            ui->label_filename->setText("Please select a filename");
            ui->label_filename->setVisible(true);
        }

    }else{
        deviceSelected = ui->comboBoxStart->currentText();
        set_deviceSelectedGeneral(deviceSelected);
        set_filenameSelectedGeneral(filenameSelected);



        if (filenameSelected != "") {

            ProcessWorker *process = new ProcessWorker(this);
            qint64 pid;

            connect(process,SIGNAL(processOutput(QString)),this,SLOT(on_processReadyToRead(QString)));
            connect(process,SIGNAL(stateReady(int,QString,QString,qint64, QString)),this,SLOT(on_processStatusReady(int,QString,QString,qint64, QString)));

            process->process(deviceSelected,filenameSelected,destinationStorage);
            pid = process->processId();

            setProcessID(pid);

            this->close();


        } else {
            ui->label_filename->setStyleSheet("QLabel { color : red; }");
            ui->label_filename->setText("Please select a filename");
            ui->label_filename->setVisible(true);
        }

    }

}

void DialogStart::on_buttonBox_rejected()
{
    this->close();

}

void DialogStart::setDevicesReady(const QStringList &parentList)
{
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

void DialogStart::setProcessID(qint64 id){
    processIDGeneral = id;
}

qint64 DialogStart::getProcessID(){

    return processIDGeneral;
}

QString DialogStart::get_deviceSelectedGeneral()
{
    return deviceSelectedGeneral;
}

QString DialogStart::get_filenameSelectedGeneral()
{
    return filenameSelectedGeneral;
}

//void DialogStart::send_Device_Filename(){

//    QSysInfo wichOS;

//    if(wichOS.kernelType() == "darwin"){
//        Misc volumeInfo;
//        QString volumeSelected;
//        volumeSelected = volumeInfo.get_OSXvolumes(ui->comboBoxStart->currentText());
//        emit deviceFilename(ui->comboBoxStart->currentText(), volumeSelected);
//    }
//    else emit deviceFilename(ui->comboBoxStart->currentText(), ui->lineEditStart->text());
//}

void DialogStart::on_comboBoxStart_currentTextChanged(const QString &arg1)
{

    for (int i = 0; i < devReadyVolumes.size();i++) {

        if (devReadyVolumes.at(i).contains(arg1)) {
            QStringList temp1 = devReadyVolumes.at(i).split("\n");
            QString temp2 = temp1.at(1);
            temp2.replace("Label: ", "");
            ui->label_VolumeName->setText(temp2);
        }
    }

}

void DialogStart::on_lineEditStart_textChanged(const QString &arg1)
{
    QString temp = arg1.trimmed();

    if((temp.isEmpty() == false) || (temp.isNull() == false))
        ui->label_filename->setText("");
}
