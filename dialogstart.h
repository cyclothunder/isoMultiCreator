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

private:
    Ui::DialogStart *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListPathOnlyModel;

    Commands *startNewJob;
};

#endif // DIALOGSTART_H
