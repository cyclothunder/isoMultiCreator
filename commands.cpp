#include "commands.h"
#include <QString>
#include <QtCore>
#include <QDebug>
#include <QProcess>

Commands::Commands()
{

}

Commands::~Commands()
{

}

QString Commands::startJob(QString deviceSelected)
{
    // QString origem = "deviceSelected";

    QString origem = "/dev/disk1s0";
    qDebug() << origem;

    QProcess process1;
    QString command;
    QStringList args;

    command = "cat";
    args << origem << "> /tmp/test.iso";


    process1.start("cat /dev/disk1s0 > /tmp/test.iso");
    process1.waitForFinished();

    QString stdOut = process1.readAllStandardOutput();
    QString stdError = process1.readAllStandardError();

    qDebug() << stdOut;
    qDebug() << stdError;

    // QProcess::execute("umount /dev/disk2");
    // QProcess::execute("cat /dev/disk2 > /tmp/test.iso");
    return origem;
}

void Commands::run()
{
    qDebug() << "Running";

}
