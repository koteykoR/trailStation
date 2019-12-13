#-------------------------------------------------
#
# Project created by QtCreator 2018-12-19T10:38:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trail_station
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        trailstation.cpp \
    carriage.cpp \
    trainway.cpp \
    train.cpp \
    admin.cpp \
    trainwaystorage.cpp \
    dialoglogin.cpp \
    adminwidget.cpp \
    user.cpp \
    cashier.cpp \
    cashierwidget.cpp \
    userstorage.cpp \
    passenger.cpp \
    passengerwidget.cpp

HEADERS  += trailstation.h \
    carriage.h \
    trainway.h \
    train.h \
    admin.h \
    trainwaystorage.h \
    dialoglogin.h \
    adminwidget.h \
    user.h \
    cashier.h \
    cashierwidget.h \
    userstorage.h \
    passenger.h \
    passengerwidget.h

FORMS    += trailstation.ui \
    dialoglogin.ui \
    adminwidget.ui \
    cashierwidget.ui \
    passengerwidget.ui
