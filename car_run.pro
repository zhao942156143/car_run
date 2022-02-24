#-------------------------------------------------
#
# Project created by QtCreator 2019-08-26T15:21:43
#
#-------------------------------------------------

QT       += core gui serialport widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L$$PWD/lib -lControlCAN

TARGET = zhaoce4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataconvert.cpp \
    datastruct.cpp \
    qcustomplot.cpp \
    canconnect.cpp \
    comconnect.cpp

HEADERS  += mainwindow.h \
    dataconvert.h \
    datastruct.h \
    qcustomplot.h \
    canconnect.h \
    controlcan.h \
    comconnect.h

FORMS    += mainwindow.ui
