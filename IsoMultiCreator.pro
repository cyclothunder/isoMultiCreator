#-------------------------------------------------
#
# Project created by QtCreator 2015-04-16T00:19:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = IsoMultiCreator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    misc.cpp \
    dialogstart.cpp \
    dialogstop.cpp \
    dialogeject.cpp \
    dialogstopconfirm.cpp \
    commands.cpp \
    ProcessWorker.cpp

HEADERS  += mainwindow.h \
    misc.h \
    dialogstart.h \
    dialogstop.h \
    dialogeject.h \
    dialogstopconfirm.h \
    commands.h \
    ProcessWorker.h

FORMS    += mainwindow.ui \
    dialogstart.ui \
    dialogstop.ui \
    dialogeject.ui \
    dialogejectconfirm.ui \
    dialogstopconfirm.ui
