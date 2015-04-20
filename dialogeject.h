#ifndef DIALOGEJECT_H
#define DIALOGEJECT_H

#include <QDialog>
#include <misc.h>
#include <QStringListModel>
#include <dialogstopconfirm.h>

namespace Ui {
class DialogEject;
}

class DialogEject : public QDialog
{
    Q_OBJECT

public:
    explicit DialogEject(QWidget *parent = 0);
    ~DialogEject();

signals:
    void processStateReady(int state, QString sourceDevice);

private slots:
    void on_buttonBox_accepted();
    void on_processStatusReady(const int state, const QString &sourceDevice);

private:
    Ui::DialogEject *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    DialogStopConfirm *dialog_StopConfirm;
};

#endif // DIALOGEJECT_H
