#include "misc.h"
#include "ProcessWorker.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QStorageInfo>

Misc::Misc()
{
devicesCurrentState = get_ROdevicesInfo();
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

void Misc::setDevicesCurrentState(QStringList parentList){
    devicesCurrentState = parentList;
}


void Misc::setDevicesReady(QStringList parentList){
    devicesReady = parentList;

}

void Misc::setDevicesNotReady(QStringList parentList){
    devicesNotReady = parentList;

}

QStringList Misc::getDevicesCurrentState(){
    // devicesCurrentState = new QStringListModel();

    if (devicesCurrentState.isEmpty()){
        // QStringList tempDeviceList;
        devicesCurrentState = get_ROdevicesInfo();
    }
    else{

        QStringList temp = get_ROdevicesInfo();
        int deviceCount;

        if (temp.size() > devicesCurrentState.size()) {
            deviceCount = temp.size();
            for (int var = 0; var < deviceCount; var++) {
                if (var < devicesCurrentState.size()) {

                    if (devicesCurrentState.at(var).startsWith("State")) {
                        temp.replace(var,devicesCurrentState.at(var));
                    }
                }

            }

            devicesCurrentState = temp;

        }else{
            deviceCount = devicesCurrentState.size();
            for (int var = 0; var < deviceCount; var++) {
                if (var < temp.size()) {

                    if (temp.at(var).startsWith("State:")) {
                        devicesCurrentState.replace(var,temp.at(var));
                    }
                }
            }
            devicesCurrentState = temp;
        }


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
