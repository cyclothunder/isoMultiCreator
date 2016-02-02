#include "misc.h"
#include "ProcessWorker.h"
#include <QStringList>
#include <QString>
#include <QStringListModel>
#include <QStorageInfo>
#include <QFileInfoList>

Misc::Misc()
{
devicesCurrentState = get_ROdevicesInfo();
devicesReady = QStringList();
devPidMap["a"] = 10000;
hddListCounter = 0;
currentHardDiskList = get_HardDrivesInfo();
}

Misc::~Misc()
{

}

hardDisk *Misc::get_HardDrivesInfo()
{

    QStringList deviceInfo;
    QDir dirs;
    QString item;

    foreach (const QFileInfo drivesList, dirs.drives()){
        qDebug() << "Drive List: " << drivesList.absolutePath();
    }

    int i=0;

    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
           if (deviceList.isValid() && deviceList.isReady()) {
               if (!deviceList.isReadOnly()) {
                   i++;
               }
           }
    }
     hddListCounter = i;
     hardDisk* hardDiskStruc = new hardDisk[i];

    i=0;
    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
           if (deviceList.isValid() && deviceList.isReady()) {
               if (!deviceList.isReadOnly()) {

                   QString itemDisplayNameFix;
                   // deviceName << deviceList.device();
                   itemDisplayNameFix = deviceList.displayName();
                   itemDisplayNameFix.replace("\\x20", " ");
                   item.append("Label: " + itemDisplayNameFix + "\n");
                   item.append("Device: " + deviceList.device() + "\n");

                   qint64 total_diskSize = deviceList.bytesTotal();
                   qint64 total_diskSize_temp = 0;

                   while (total_diskSize >= 1024) {
                       total_diskSize_temp = total_diskSize/1024;
                       total_diskSize = total_diskSize_temp;
                   }

                   item.append("Total: " + QString::number(total_diskSize) + " Gb" + "\n"); // Convert to Gb

                   qint64 free_diskSize = deviceList.bytesFree();
                   qint64 free_diskSize_temp = 0;

                   while (free_diskSize >= 1024) {
                       free_diskSize_temp = free_diskSize/1024;
                       free_diskSize = free_diskSize_temp;
                   }

                   item.append("Free: " + QString::number(free_diskSize) + " Gb" + "\n"); // Convert to Gb
                   item.append("State: Ready\n\n");
                   deviceInfo << item;

                   hardDiskStruc[i].label = itemDisplayNameFix;
                   hardDiskStruc[i].device = deviceList.device();
                   hardDiskStruc[i].totalBytes = QString::number(total_diskSize);
                   hardDiskStruc[i].freeBytes = QString::number(free_diskSize);
                   hardDiskStruc[i].state = "Ready";
                   ++i;
             }
          }
     }

    for (int var = 0; var < i; var++) {
        qDebug() << "Label -" << hardDiskStruc[var].label;
        qDebug() << "Device -" << hardDiskStruc[var].device;
        qDebug() << "Total -" << hardDiskStruc[var].totalBytes << "Gb";
        qDebug() << "Free -" << hardDiskStruc[var].freeBytes << "Gb";
        qDebug() << "State -" << hardDiskStruc[var].state;
        qDebug() << "------ empty line ------";

    }

    return hardDiskStruc;
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
    QDir dirs;

    foreach (const QFileInfo drivesList, dirs.drives()){
        qDebug() << drivesList.absolutePath();
    }



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

void Misc::setHDDCurrentState(QString parentHddState, QString parentDestinationStorage){

    int hddListCount = 0;
    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
           if (deviceList.isValid() && deviceList.isReady()) {
               if (!deviceList.isReadOnly()) {
                   hddListCount++;
               }
           }
    }

    for(int hddcount = 0; hddcount < hddListCount; hddcount++){

        if(currentHardDiskList[hddcount].label == parentDestinationStorage){
//            if(hddList[hddcount].state == "Ready" ) hddList[hddcount].state = "Busy";
//            else hddList[hddcount].state = "Ready";
            currentHardDiskList[hddcount].state = parentHddState;

            qDebug() << "-----> destinationstorage: " << parentDestinationStorage;
            qDebug() << "hdd label: " << currentHardDiskList[hddcount].label;
            qDebug() << "hdd state: " << parentHddState;
        }
        else qDebug() << "hdd not found!";
    }


}

void Misc::insertHddCDromMAP(QString parentState, QString parentDestinationStorage, QString parentCDrom){

    hdd_cdromStateUpdated.insertMulti(parentDestinationStorage, parentCDrom);
    setHDDCurrentState(parentState, parentDestinationStorage);

}

void Misc::removeHddCDromMAP(QString parentCDrom){

    QString currentStorageToStop = hdd_cdromStateUpdated.key(parentCDrom);

    hdd_cdromStateUpdated.remove(currentStorageToStop, parentCDrom);

    if ( hdd_cdromStateUpdated.contains(currentStorageToStop) == true ){

        setHDDCurrentState("Busy", currentStorageToStop);
    }
    else setHDDCurrentState("Ready", currentStorageToStop);

}

hardDisk *Misc::getHDDCurrentState(){
    return currentHardDiskList;
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

    QStringList temp;
//    if (devicesReady.isEmpty()) {
//        devicesReady = get_ROdevicesPath();

        for (int x = 0; x < devicesCurrentState.size(); x++) {

            if (devicesCurrentState.at(x).contains("Ready") == true) {

                deviceName = devicesCurrentState.at(x).split("\n");


                temp.append(deviceName.at(0));
            }

        }
    // }
        temp.replaceInStrings("Device: ", "");
        devicesReady = temp;
    return devicesReady;
}

QStringList Misc::getDevicesNotReady()
{

    QStringList temp;
//    if (devicesReady.isEmpty()) {
//        devicesReady = get_ROdevicesPath();

        for (int x = 0; x < devicesCurrentState.size(); x++) {

            if (devicesCurrentState.at(x).contains("Running") == true) {

                deviceName = devicesCurrentState.at(x).split("\n");


                temp.append(deviceName.at(0));
            }

        }
    // }
        temp.replaceInStrings("Device: ", "");
        devicesNotReady = temp;

    return devicesNotReady;
}

void Misc::setDevPID(QString device, qint64 pid){

    devPidMap[device] = pid;
}

qint64 Misc::getDevPID(QString devices){

    qint64 currentPID = devPidMap.value(devices);
    return currentPID;
}

QMap<QString, qint64> Misc::getMapDevPid(){
    return devPidMap;
}

void Misc::toggleHddState(QString dev){
//    for (int var = 0; var < hddListCounter; ++var) {
//        if (currentHardDiskList[var].device.contains(dev) & currentHardDiskList[var].state == "Ready") {
//            currentHardDiskList[var].state = "Busy";
//        } else {
//            if (currentHardDiskList[var].device.contains(dev) & currentHardDiskList[var].state == "Busy") {
//                currentHardDiskList[var].state = "Ready";

//            }
//        }
//    }
}
