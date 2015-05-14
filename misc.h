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
    QStringList setDevicesReady(QStringList parentList);
    QStringList setDevicesNotReady(QStringList parentList);
    QStringListModel *setDevicesCurrentState(QStringListModel &parentListModel);
    QStringList getDevicesReady();
    QStringList getDevicesNotReady();

    QStringList devicesReady, devicesNotReady;
    // QStringList deviceListPath;
    QStringListModel *devicesCurrentState = new QStringListModel();

    QStringListModel *getDevicesCurrentState();
    QString get_OSXvolumes(QString parentDevice);
};

#endif // MISC_H
