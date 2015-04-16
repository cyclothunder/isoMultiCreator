#ifndef MISC_H
#define MISC_H

#include <QStringList>


class Misc
{
public:
    Misc();
    ~Misc();
    QStringList get_ROdevicesInfo();
    QStringList get_ROdevicesPath();
};

#endif // MISC_H
