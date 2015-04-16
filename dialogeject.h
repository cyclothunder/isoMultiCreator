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

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DialogEject *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    DialogStopConfirm *dialog_StopConfirm;
};

#endif // DIALOGEJECT_H
