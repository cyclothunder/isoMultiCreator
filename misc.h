#ifndef MISC_H
#define MISC_H

#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QDebug>

struct hardDisk {
    QString label;
    QString device;
    QString totalBytes;
    QString freeBytes;
    QString state;
};

class Misc
{
public:
    Misc();
    ~Misc();
    QStringList get_ROdevicesInfo();
    QStringList get_ROdevicesPath();
    hardDisk *get_HardDrivesInfo();
    hardDisk* hardDiskStruc ;
    hardDisk* currentHardDiskList;
    void setDevicesReady(QStringList parentList);
    void setDevicesNotReady(QStringList parentList);
    void setDevicesCurrentState(QStringList parentList);
    QStringList getDevicesReady();
    QStringList getDevicesNotReady();
    QStringList devicesCurrentState, deviceName;
    QStringList devicesReady, devicesNotReady;
    QMap<QString, qint64> devPidMap;
    int hddListCounter;
    // hardDisk hardDiskStruc[0];
    // QStringList deviceListPath;

    hardDisk *getHDDCurrentState();
    void setHDDCurrentState(QString parentHddState, QString parentDestinationStorage);

    QStringList getDevicesCurrentState();
    QString get_OSXvolumes(QString parentDevice);

    void setDevPID(QString device, qint64 pid);
    qint64 getDevPID(QString devices);
    QMap<QString, qint64> getMapDevPid();
    void toggleHddState(QString dev);
};

#endif // MISC_H
