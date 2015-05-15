#include "misc.h"
#include "ProcessWorker.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QStorageInfo>

Misc::Misc()
{
devicesCurrentState = get_ROdevicesInfo();
devicesReady = QStringList();
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
               deviceName << deviceList.device();
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
    
    QStringList temp = get_ROdevicesInfo();

    int devicesAllReady = 0;
    if (temp.size() >= devicesCurrentState.size()) {
        int deviceHit = 0;
        for (int x = 0; x < devicesCurrentState.size(); x++) {

            if (devicesCurrentState.at(x).contains("Ready") == false) {

                deviceName = devicesCurrentState.at(x).split("\n");

                for(int i = 0; i < temp.size(); i++){

                    if (temp.at(i).contains(deviceName.at(0)) == true) {

                        deviceHit += 1;
                        devicesAllReady += 0;
                        temp.replace(i, devicesCurrentState.at(x) );

                    }
                }

                
            }

        }

        devicesCurrentState = temp;
        
    } else {
        if ((temp.size() < devicesCurrentState.size()) && (temp.size() > 0)) {
            for (int x = 0; x < devicesCurrentState.size(); ++x){
               int deviceHit = 0;
               deviceName = devicesCurrentState.at(x).split("\n");
               for(int i = 0; i < temp.size(); i++){
                   if(temp.at(i).contains(deviceName.at(0)) == true){
                        if (devicesCurrentState.at(x).contains("Ready") == false) temp.replace(i, devicesCurrentState.at(x) );
                       deviceHit += 1;
                       // break;
                   }
                   else {
                       deviceHit += 0;
                   }
               }

               if(deviceHit == 0){
                devicesCurrentState.removeAt(x);
                x -= 1;
               }
            }
        }
        else devicesCurrentState = get_ROdevicesInfo();
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
