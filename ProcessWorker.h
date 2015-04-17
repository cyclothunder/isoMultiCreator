#ifndef PROCESSWORKER_H
#define PROCESSWORKER_H

#include <QProcess>
//#include <workoptionsdialog.h>

class ProcessWorker : public QProcess
{
    Q_OBJECT
public:
    explicit ProcessWorker(QObject *parent = 0);

private:


signals:
    void processOutput(QString output);

public slots:
    void process(const QString &parentDevice, const QString &parentDestination);

private slots:
    void onProcessReadyToRead();
    void onFinished(int exitCode,QProcess::ExitStatus status);

};

#endif // PROCESSWORKER_H
