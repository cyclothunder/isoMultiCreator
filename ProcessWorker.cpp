#include "ProcessWorker.h"
#include <QDateTime>
#include <QDebug>


QString device;

ProcessWorker::ProcessWorker(QObject *parent):
    QProcess(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(onProcessReadyToRead()));
    connect(this,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(onFinished(int,QProcess::ExitStatus)));
    connect(this,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(onStateChange()));

}

void ProcessWorker::process(const QString &parentDevice, const QString &parentDestination)
{


    sourceDevice = parentDevice;
    destinationDevice = parentDestination;

    QStringList args;
    args << "if=" + sourceDevice << "of=" + destinationDevice << "bs=1";

    //dd if=/dev/sr2 of=/tmp/test.iso bs=1

    qDebug() << "Starting Process for " + parentDevice;
    this->start("/bin/dd",args);
    this->waitForStarted();



}

void ProcessWorker::onProcessReadyToRead()
{

    if (!this->isOpen()) this->open(QIODevice::ReadOnly);
    QString output = QString::fromLatin1(this->readAll());

    // YOUR CODE HERE

    emit processOutput(output);
}

void ProcessWorker::onFinished(int exitCode, QProcess::ExitStatus status)
{

    if (this->state() == 2 || status == QProcess::CrashExit) {
        this->close();
        this->terminate();
        this->waitForFinished(-1);
        emit finished(exitCode);
    } else emit finished(exitCode);
    qDebug() << "Process Finished for " + sourceDevice;
}

void ProcessWorker::onStateChange()
{
    emit stateReady(this->state(),sourceDevice);

}

QString ProcessWorker::ProcessState()
{
   QString ret;

   if(this->state() == QProcess::NotRunning) ret = "NotRunning";
   if(this->state() == QProcess::Starting) ret = "Starting";
   if(this->state() == QProcess::Running) ret = "Running";

   return ret;
}
