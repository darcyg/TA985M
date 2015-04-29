#-------------------------------------------------
#
# Project created by QtCreator 2014-12-11T09:46:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ta985m
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           src/modbustcp.cpp \
           3rdparty/libmodbus/modbus.c      \
           3rdparty/libmodbus/modbus-tcp.c \
           3rdparty/libmodbus/modbus-rtu.c \
           3rdparty/libmodbus/modbus-data.c \
    src/viewbd.cpp \
    src/dmanualloadmss.cpp \
    src/dmssfileset.cpp \
    src/dmanualpvd.cpp \
    src/dsdatamodel.cpp \
    src/dmanuamag.cpp \
    src/dselftest.cpp \
    src/dmanualkommss.cpp \
    src/dcheckpvd.cpp

HEADERS  += mainwindow.h \
            src/ta985m.h \
            src/modbustcp.h \
            3rdparty/libmodbus/modbus.h \
            3rdparty/libmodbus/modbus-version.h \
            3rdparty/libmodbus/modbus-tcp.h \
            3rdparty/libmodbus/modbus-tcp-private.h \
            3rdparty/libmodbus/modbus-rtu.h \
            3rdparty/libmodbus/modbus-rtu-private.h \
            3rdparty/libmodbus/modbus-private.h \
            3rdparty/libmodbus/config.h \
    # ../TK168/src/tk168_config.h \
    src/viewbd.h \
    src/dmanualloadmss.h \
    src/dmssfileset.h \
    src/dmanualpvd.h \
    src/dsdatamodel.h \
    src/dmanuamag.h \
    src/dselftest.h \
    src/dmanualkommss.h \
    src/dcheckpvd.h

FORMS    += mainwindow.ui \
    src/viewbd.ui \
    src/dmanualloadmss.ui \
    src/dmssfileset.ui \
    src/dmanualpvd.ui \
    src/dmanuamag.ui \
    src/dselftest.ui \
    src/dmanualkommss.ui \
    src/dcheckpvd.ui


INCLUDEPATH += 3rdparty/libmodbus


win32:DEFINES += _TTY_WIN_  WINVER=0x0501
win32:LIBS += -lsetupapi -lwsock32 -lws2_32
