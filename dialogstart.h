#ifndef DIALOGSTART_H
#define DIALOGSTART_H

#include <QDialog>
#include <misc.h>
#include <QStringListModel>
#include <QMessageBox>

namespace Ui {
class DialogStart;
}

class DialogStart : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStart(const QStringList devList, QWidget *parent = 0);
    ~DialogStart();

    void setDevicesReady(const QStringList &parentList);
    QStringList getDevicesReady();

    QStringList startDevicesReady;

    void set_deviceSelectedGeneral(QString &sourceDevice);

    QString get_deviceSelectedGeneral();

    void set_filenameSelectedGeneral(QString &filename);

    QString get_filenameSelectedGeneral();

    QString filenameSelectedGeneral, deviceSelectedGeneral;

    QStringList devReadyVolumes;

    qint64 processIDGeneral;

    void setProcessID(qint64 id);

    QString deviceSelected;

    qint64 getProcessID();
    QString destinationStorage;

public slots:

//    void on_send_SourceDestination(QString source, QString destination);
//    void send_Device_Filename();

private slots:

    void on_processReadyToRead(const QString &output);

    void on_pushButton_clicked();

    void on_processStatusReady(const int state, const QString &sourceDevice, const QString &destination, const qint64 &pid, QString const destinationStorage);


    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBoxStart_currentTextChanged(const QString &arg1);

    void on_lineEditStart_textChanged(const QString &arg1);

private:
    Ui::DialogStart *ui;

    Misc *deviceListPathOnly;
    QStringListModel *deviceListReadyModel;


signals:
    void processStateReady(int state, QString sourceDevice, QString destination, qint64 pid, QString destinationStorage);
    void processReadyToReadOutput(const QString &output);
    void send_SourceDestination(QString source, QString destination);
    void deviceFilename(QString thisSourceDevice, QString thisDestinationDevice);
};

#endif // DIALOGSTART_H
