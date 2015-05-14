#include "misc.h"
#include "ProcessWorker.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QStorageInfo>

Misc::Misc()
{

}

Misc::~Misc()
{

}


QString Misc::get_OSXvolumes(QString parentDevice){

    // QStringList deviceVolumeInfo;
    QString item;

    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
        if (deviceList.isValid() /*&& deviceList.isReady()*/) {
            if (deviceList.isReadOnly()) {

               if(deviceList.device() == parentDevice){
                    item.append(deviceList.displayName());
                    break;
               }
              }
         }
     }

     // deviceVolumeInfo << item;
     return item;
}

QStringList Misc::get_ROdevicesInfo()
{

    QStringList deviceInfo;


    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
        if (deviceList.isValid() /*&& deviceList.isReady()*/) {
            if (deviceList.isReadOnly()) {
               QString item, itemDisplayNameFix;
               item.append("Device: " + deviceList.device() + "\n");
               // deviceListPath << deviceList.device();
               itemDisplayNameFix = deviceList.displayName();
               itemDisplayNameFix.replace("\\x20", " ");
               item.append("Label: " + itemDisplayNameFix + "\n");
               item.append("Size: " + QString::number(deviceList.bytesTotal()/1024/1024) + " MB" + "\n"); // Convert to MB
               item.append("State: Ready\n");
                deviceInfo << item;
              }
         }
     }

     return deviceInfo;
}

QStringList Misc::get_ROdevicesPath()
{

    QStringList deviceListPath;

    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
            if (deviceList.isValid() /*&& deviceList.isReady()*/) {
                if (deviceList.isReadOnly()) {

                   deviceListPath << deviceList.device();

                  }
             }
         }

    return deviceListPath;

}

QStringListModel *Misc::setDevicesCurrentState(QStringListModel &parentListModel){
    // devicesCurrentState = &parentListModel;
    return &parentListModel;
}


QStringList Misc::setDevicesReady(QStringList parentList){
    devicesReady = parentList;
    return devicesReady;
}

QStringList Misc::setDevicesNotReady(QStringList parentList){
    devicesNotReady = parentList;
    return devicesNotReady;
}

QStringListModel *Misc::getDevicesCurrentState(){
    // devicesCurrentState = new QStringListModel();

    if (devicesCurrentState->rowCount() == 0){
        // QStringList tempDeviceList;
        devicesCurrentState->setStringList(get_ROdevicesInfo());
    }
    return devicesCurrentState;
}

QStringList Misc::getDevicesReady()
{
    if (devicesReady.isEmpty()) {
        devicesReady = get_ROdevicesPath();
    }
    return devicesReady;
}

QStringList Misc::getDevicesNotReady()
{
    return devicesNotReady;
}
