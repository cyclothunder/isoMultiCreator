#include "misc.h"
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

               deviceInfo << "Device: " + deviceList.device();
               // deviceListPath << deviceList.device();
               deviceInfo << "Label: " + deviceList.displayName();
               deviceInfo << "Size: " + QString::number(deviceList.bytesTotal()/1024/1024) + " MB"; // Convert to MB
               deviceInfo << ""; // Space between devices

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
