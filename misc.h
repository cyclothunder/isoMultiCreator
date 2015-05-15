#ifndef MISC_H
#define MISC_H

#include <QStringList>
#include <QString>
#include <QStringListModel>


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
    // QStringList deviceListPath;


    QStringList getDevicesCurrentState();
    QString get_OSXvolumes(QString parentDevice);



};

#endif // MISC_H
