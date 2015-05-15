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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();




signals:
    void on_processStateChange();
    void deviceListReady();

private slots:
    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButtonEject_clicked();

    void on_pushButtonRefresh_clicked();

    void on_processStateChange(const int state, const QString &sourceDevice);


private:
    Ui::MainWindow *ui;

    Misc *deviceInfoList;
    Misc deviceInfoListStateUpdated;

    QStringListModel *deviceInfoListModel;

    DialogStart *dialog_StartJob;
    DialogStop *dialog_StopJob;
    DialogEject *dialog_eject;
    QStringList deviceReady, deviceNotReady, deviceStateUpdated;
    QStringList deviceReadyAfterOpened;
    QStringList deviceNotReadyAfterOpened;



};

#endif // MAINWINDOW_H
