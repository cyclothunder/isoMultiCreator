#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogstart.h"
#include "dialogstop.h"
#include "dialogeject.h"
#include "misc.h"
#include "ProcessWorker.h"
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

struct devices {
    qint64 pid;
    int state;
    QString deviceName;

} ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer *timer;
    QMap<QString, QString> filenameMap;
    QMap<QString, qint64> devPidList, hddPidList;
    devices *devicePidListStruct[0];
    int structSize;


signals:
    void on_processStateChange();
    void deviceListReady();

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonEject_clicked();

//    void on_pushButtonRefresh_clicked();

    void on_processStateChange(const int state, const QString &sourceDevice, const QString &destination, const qint64 &pid, const QString destinationStorage);

    void deviceListUpdate();

    void readOutput(QString output);


private:
    Ui::MainWindow *ui;

    Misc *deviceInfoList;
    Misc deviceInfoListStateUpdated;

    hardDisk *hddList;
    int hddListCount;

    QStringListModel *deviceInfoListModel, *deviceInfoListModel2;

    DialogStart *dialog_StartJob;
    DialogStop *dialog_StopJob;
    DialogEject *dialog_eject;
    QStringList deviceReady, deviceNotReady, deviceStateUpdated, hddNotReady;
    QStringList deviceReadyAfterOpened;
    QStringList deviceNotReadyAfterOpened;

    QString onStateChangeToRunning, hddState;

    void set_Device_onStateChangeToRunning();
    QString get_Device_onStateChangeToRunning(QString deviceChangedToRunning);



};

#endif // MAINWINDOW_H
