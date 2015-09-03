#ifndef COMMANDS_H
#define COMMANDS_H

#include <QString>

struct hardDisk {
    QString label;
    QString device;
    QString totalBytes;
    QString freeBytes;
    QString state;
};

class Commands
{
public:
    Commands();
    ~Commands();

};

#endif // COMMANDS_H
