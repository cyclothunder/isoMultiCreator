#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <misc.h>
#include <QStringListModel>
#include <commands.h>

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
    void on_dialogButtonBoxStart_accepted();
    void on_processReadyToRead(const QString &output);

    void on_pushButton_clicked();

    void on_processStatusReady(const int state, const QString &sourceDevice);

private:
    Ui::DialogStart *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    Commands *startNewJob;

signals:
    void processStateReady(int state, QString sourceDevice);
};

#endif // DIALOGSTART_H
