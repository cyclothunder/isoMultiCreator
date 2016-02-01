#include "dialogstop.h"
#include "ui_dialogstop.h"


DialogStop::DialogStop(const QStringList devList, QMap<QString, qint64> parentMap, QMap<QString, qint64> parentHddMap, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogStop)
{
    ui->setupUi(this);
    deviceListPathOnly = new Misc;

    currentDevPidMap = parentMap;
    currentHddPidMap = parentHddMap;

    QMapIterator<QString, qint64> iter_currentDevPidMap(currentHddPidMap);

    while(iter_currentDevPidMap.hasNext()){
        iter_currentDevPidMap.next();
        qDebug() << "DIALOG STOP . device: "<< iter_currentDevPidMap.key() << "pid: "<< iter_currentDevPidMap.value();
    }

    QStringListModel *newList = new QStringListModel(devList);
    ui->comboBoxStop->setModel(newList);

    if (ui->comboBoxStop->currentText() == "") {
        ui->label_allReady->setStyleSheet("QLabel { color : red; }");
        ui->label_allReady->setVisible(true);
    }else {

        devReadyVolumes = deviceListPathOnly->getDevicesCurrentState();

        for (int i = 0; i < devReadyVolumes.size();i++) {

            if (devReadyVolumes.at(i).contains(ui->comboBoxStop->currentText())) {
                QStringList temp1 = devReadyVolumes.at(i).split("\n");
                QString temp2 = temp1.at(1);

                // temp2.replace("Label: ", "");

                ui->label_allReady->setText(temp2);
                ui->label_allReady->setVisible(true);

            }
        }


     }
}

DialogStop::~DialogStop()
{
    delete ui;
}

void DialogStop::on_buttonBoxStop_accepted()
{

//        dialog_StopConfirm = new DialogStopConfirm(this);
//        dialog_StopConfirm->setWindowTitle("WARNING");
//        dialog_StopConfirm->show();


        QMessageBox::StandardButton msgBox;

        msgBox = QMessageBox::question(this, "This will terminate current Job and eject CD.", "Are you sure?", QMessageBox::Ok | QMessageBox::Cancel);

//        msgBox.setText("This will terminate current Job and eject CD.");
//        msgBox.setInformativeText("Are you sure that you want to stop this job?");
//        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);


//        msgBox.setDefaultButton(QMessageBox::Cancel);

//        int ret = msgBox.exec();


        qint64 temp_pid = currentDevPidMap.value(ui->comboBoxStop->currentText());
        QString temp_hddStorage = currentHddPidMap.key(temp_pid);


        if(msgBox == QMessageBox::Ok){
            // deviceListPathOnly->setHddStoragePid(temp_hddStorage, temp_pid);
            ProcessWorker *processStop = new ProcessWorker(this);
            processStop->processKill(ui->comboBoxStop->currentText(), temp_pid);
            deviceListPathOnly->setHDDCurrentState("Ready", temp_hddStorage);
            qDebug() << "Stopping - " << temp_hddStorage << " | State: " << "Ready";
            this->close();
        }

}
