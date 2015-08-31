#ifndef MISC_H
#define MISC_H

#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QDebug>


class Misc
{
public:
    Misc();
    ~Misc();
    QStringList get_ROdevicesInfo();
    QStringList get_ROdevicesPath();
    void setDevicesReady(QStringList parentList);
    void setDevicesNotReady(QStringList parentList);
    void setDevicesCurrentState(QStringList parentList);
    QStringList getDevicesReady();
    QStringList getDevicesNotReady();
    QStringList devicesCurrentState, deviceName;
    QStringList devicesReady, devicesNotReady;
    QMap<QString, qint64> devPidMap;
    // QStringList deviceListPath;


    QStringList getDevicesCurrentState();
    QString get_OSXvolumes(QString parentDevice);

    void setDevPID(QString device, qint64 pid);
    qint64 getDevPID(QString devices);
    QMap<QString, qint64> getMapDevPid();
};

#endif // MISC_H
