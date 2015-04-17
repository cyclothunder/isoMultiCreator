#include "ProcessWorker.h"
#include <QDateTime>

ProcessWorker::ProcessWorker(QObject *parent):
    QProcess(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(onProcessReadyToRead()));
    connect(this,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(onFinished(int,QProcess::ExitStatus)));

}

void ProcessWorker::process(const QString &parentDevice, const QString &parentDestination)
{

    QString device = parentDevice;
    QString destination = parentDestination;

    QStringList args;
    args << device << destination;

    this->start("cat",args);
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
}
