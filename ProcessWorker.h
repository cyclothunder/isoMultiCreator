#ifndef PROCESSWORKER_H
#define PROCESSWORKER_H

#include <QProcess>
#include <QTimer>
//#include <workoptionsdialog.h>

#include "misc.h"

class ProcessWorker : public QProcess
{
    Q_OBJECT
public:
    explicit ProcessWorker(QObject *parent = 0);
    QString ProcessState();

    void processKill(const QString &parentDevice, const qint64 &parentPid);

private:
    QString sourceDevice, destinationDevice, volumeDevice;
    QTimer *timer;
    qint64 processPid;

signals:
    void processOutput(QString output);
    void stateReady(int state, QString thisSourceDevice, QString thisDestination, qint64 thisPid);


public slots:
    void process(const QString &parentDevice, const QString &parentDestination);
    void process(const QString &parentDevice, const QString &parentDestination, const QString &parentVolume);
    void processEject(const QString &parentDevice);


private slots:
    void onProcessReadyToRead();
    void onFinished(int exitCode,QProcess::ExitStatus status);
    void onStateChange();


};

#endif // PROCESSWORKER_H
