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



public slots:

    void on_send_SourceDestination(QString source, QString destination);
    void send_Device_Filename();

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
    void send_SourceDestination(QString source, QString destination);
    void deviceFilename(QString thisSourceDevice, QString thisDestinationDevice);
};

#endif // DIALOGSTART_H
