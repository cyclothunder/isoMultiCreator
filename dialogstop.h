#ifndef DIALOGSTOP_H
#define DIALOGSTOP_H

#include <QDialog>
#include <misc.h>
#include <dialogstopconfirm.h>
#include <QStringListModel>

namespace Ui {
class DialogStop;
}

class DialogStop : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStop(QWidget *parent = 0);
    ~DialogStop();

private slots:
    void on_buttonBoxStop_accepted();

private:
    Ui::DialogStop *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    DialogStopConfirm *dialog_StopConfirm;

};

#endif // DIALOGSTOP_H
