#include "misc.h"
#include "ProcessWorker.h"
#include <QStringList>
#include <QStorageInfo>

Misc::Misc()
{

}

Misc::~Misc()
{

}



QStringList Misc::get_ROdevicesInfo()
{

    QStringList deviceInfo;


    foreach (const QStorageInfo &deviceList, QStorageInfo::mountedVolumes()){
        if (deviceList.isValid() /*&& deviceList.isReady()*/) {
            if (deviceList.isReadOnly()) {
               QString item;
               item.append("Device: " + deviceList.device() + "\n");
               // deviceListPath << deviceList.device();
               item.append("Label: " + deviceList.displayName() + "\n");
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
