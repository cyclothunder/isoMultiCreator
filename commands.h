#ifndef COMMANDS_H
#define COMMANDS_H
#include <QtCore>


class Commands : public QThread
{
public:
    Commands();
    ~Commands();

    QString startJob(QString deviceSelected);
    void run();
};

#endif // COMMANDS_H
