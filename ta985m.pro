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
    src/dsdatamodel.cpp

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
    ../TK168/src/tk168_config.h \
    src/viewbd.h \
    src/dmanualloadmss.h \
    src/dmssfileset.h \
    src/dmanualpvd.h \
    src/dsdatamodel.h

FORMS    += mainwindow.ui \
    src/viewbd.ui \
    src/dmanualloadmss.ui \
    src/dmssfileset.ui \
    src/dmanualpvd.ui


INCLUDEPATH += 3rdparty/libmodbus \
               /home/dimsun/work/Qt_Project/TK168/src
