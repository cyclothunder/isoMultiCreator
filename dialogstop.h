#ifndef DIALOGSTOP_H
#define DIALOGSTOP_H

#include <QDialog>
#include <misc.h>
#include <dialogstopconfirm.h>
#include <QStringListModel>
#include <QMessageBox>
#include <ProcessWorker.h>

namespace Ui {
class DialogStop;
}

class DialogStop : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStop(const QStringList devList, QMap<QString, qint64> parentMap, QMap<QString, qint64> parenthddMap, QWidget *parent = 0);
    ~DialogStop();
    QMap<QString, qint64> currentDevPidMap, currentHddPidMap;
    QStringList devReadyVolumes;

private slots:
    void on_buttonBoxStop_accepted();

private:
    Ui::DialogStop *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    DialogStopConfirm *dialog_StopConfirm;

};

#endif // DIALOGSTOP_H
