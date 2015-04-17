#ifndef PROCESSWORKER_H
#define PROCESSWORKER_H

#include <QProcess>
#include <QTimer>
//#include <workoptionsdialog.h>

class ProcessWorker : public QProcess
{
    Q_OBJECT
public:
    explicit ProcessWorker(QObject *parent = 0);
    QString ProcessState();

private:
    QString sourceDevice, destinationDevice;
    QTimer *timer;

signals:
    void processOutput(QString output);
    void stateReady(int state, QString thisSourceDevice);

public slots:
    void process(const QString &parentDevice, const QString &parentDestination);

private slots:
    void onProcessReadyToRead();
    void onFinished(int exitCode,QProcess::ExitStatus status);
    void onStateChange();

};

#endif // PROCESSWORKER_H
