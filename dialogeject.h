#ifndef DIALOGEJECT_H
#define DIALOGEJECT_H

#include <QDialog>
#include <misc.h>
#include <QStringListModel>
#include <dialogstopconfirm.h>
// #include <mainwindow.h>

namespace Ui {
class DialogEject;
}

class DialogEject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEject(const QStringList devList, QWidget *parent = 0);
    ~DialogEject();


    // QStringListModel *devListModel;



signals:
    void processStateReady(int state, QString sourceDevice);
   // void processStateReady(int state, QString sourceDevice);

private slots:
    void on_buttonBox_accepted();
   // void on_processStatusReady(const int state, const QString &sourceDevice);
   // void devices_Ready_MainWindow();

   // void on_processStateChange(const int state, const QString &sourceDevice);

    void on_comboBoxEject_currentTextChanged(const QString &arg1);
    void on_processStatusReady(const int state, const QString &sourceDevice);

private:
    Ui::DialogEject *ui;

    Misc *deviceInfoList;
    Misc *deviceListPathOnly;
    QStringListModel *deviceInfoListModel;
    QStringListModel *deviceListPathOnlyModel;

    QStringList devReadyVolumes;

    DialogStopConfirm *dialog_StopConfirm;
};

#endif // DIALOGEJECT_H
