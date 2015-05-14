#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <misc.h>
#include <QStringListModel>

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(QWidget *parent = 0);
    ~DialogStart();

private slots:

    void on_processReadyToRead(const QString &output);

    void on_pushButton_clicked();

    void on_processStatusReady(const int state, const QString &sourceDevice);

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DialogStart *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListReadyModel;


signals:
    void processStateReady(int state, QString sourceDevice);
    void processReadyToReadOutput(const QString &output);
};

#endif // DIALOGSTART_H
