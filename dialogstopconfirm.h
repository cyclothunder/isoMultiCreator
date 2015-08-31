#ifndef DIALOGSTOPCONFIRM_H
#define DIALOGSTOPCONFIRM_H

#include <QDialog>

namespace Ui {
class DialogStopConfirm;
}

class DialogStopConfirm : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStopConfirm(QWidget *parent = 0);
    ~DialogStopConfirm();

private slots:
    void on_buttonBoxStopConfirm_accepted();

private:
    Ui::DialogStopConfirm *ui;
};

#endif // DIALOGSTOPCONFIRM_H
