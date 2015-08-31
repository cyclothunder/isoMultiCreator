#include "ProcessWorker.h"
#include <QDateTime>
#include <QDebug>
#include <QSysInfo>


QString device;

ProcessWorker::ProcessWorker(QObject *parent):
    QProcess(parent)
{
    connect(this,SIGNAL(readyRead()),this,SLOT(onProcessReadyToRead()));
    connect(this,SIGNAL(finished(int,QProcess::ExitStatus)),this,SLOT(onFinished(int,QProcess::ExitStatus)));
    connect(this,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(onStateChange()));

   processPid = 0;

}

void ProcessWorker::process(const QString &parentDevice, const QString &parentDestination)
{


    sourceDevice = parentDevice;
    destinationDevice = parentDestination;

    QStringList args;
    QSysInfo wichOS;

    if(wichOS.kernelType() == "darwin"){
        args << "makehybrid -iso -joliet -o " + destinationDevice << "/Volumes/"+sourceDevice;
        qDebug() << "Starting Process for " + parentDevice;

        this->start("/usr/bin/hdiutil",args);
        processPid = this->processId();

    }else{
        args << "if=" + sourceDevice << "of=" + destinationDevice << "bs=1";
        //dd if=/dev/sr2 of=/tmp/test.iso bs=1
        qDebug() << "Starting Process for " + parentDevice;
        this->start("/bin/dd",args);
        processPid = this->processId();
    }


    this->waitForStarted();

}

void ProcessWorker::process(const QString &parentDevice, const QString &parentDestination, const QString &parentVolume)
{


    sourceDevice = parentDevice;
    volumeDevice = parentVolume;
    destinationDevice = parentDestination;

    QStringList args;
    QSysInfo wichOS;

    if(wichOS.kernelType() == "darwin"){
        args << "makehybrid -iso -joliet -o " + destinationDevice << "/Volumes/"+volumeDevice;
        qDebug() << "Starting Process for " + parentDevice;

        this->start("/usr/bin/hdiutil",args);
        processPid = this->processId();

    }else{
        args << "if=" + sourceDevice << "of=" + destinationDevice << "bs=1";
        //dd if=/dev/sr2 of=/tmp/test.iso bs=1
        qDebug() << "Starting Process for " + parentDevice;
        this->start("/bin/dd",args);
        processPid = this->processId();
    }


    this->waitForStarted();

}

void ProcessWorker::processEject(const QString &parentDevice)
{
    sourceDevice = parentDevice;

    QStringList args;
    args << sourceDevice;

    qDebug() << "Starting process for ejecting " + parentDevice;
    this->start("eject",args);
    this->waitForStarted();

}

void ProcessWorker::processKill(const QString &parentDevice, const qint64 &parentPid)
{
    sourceDevice = parentDevice;

    QStringList args;

    args << QString::number(parentPid);

    qDebug() << "Killing process " << args << "for device " << sourceDevice;
    this->start("kill",args);
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
    QStringList args;
    args << sourceDevice;

    if (this->state() == 2 || status == QProcess::CrashExit) {

        this->close();
        this->terminate();
        this->waitForFinished(-1);
        emit finished(exitCode);
    } else emit finished(exitCode);

    qDebug() << "Process Finished for " + sourceDevice;
    QProcess::execute("eject",args);

    processPid = 0;
}

void ProcessWorker::onStateChange()
{
    QSysInfo wichOS;

    if(wichOS.kernelType() == "darwin")
        emit stateReady(this->state(),sourceDevice, volumeDevice, processPid);
     else emit stateReady(this->state(),sourceDevice,destinationDevice, processPid);

}

