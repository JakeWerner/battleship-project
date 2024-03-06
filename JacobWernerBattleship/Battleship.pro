#-------------------------------------------------
#
# Project created by QtCreator 2021-04-20T11:10:51
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += battleship.cpp \
           main.cpp\
           mainwindow.cpp \
           startwindow.cpp


HEADERS  += battleship.h \
            mainwindow.h \
            startwindow.h

FORMS    += mainwindow.ui \
            startwindow.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
