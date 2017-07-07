#-------------------------------------------------
#
# Project created by QtCreator 2017-07-06T15:00:21
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tools
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sparse.cpp

HEADERS  += mainwindow.h \
    sparse.h

FORMS    += mainwindow.ui \
    sparse.ui

RESOURCES += \
    image.qrc
