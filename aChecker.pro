#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T21:15:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aChecker
TEMPLATE = app


SOURCES += \
    src/finitestateautomaton.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/state.cpp \
    src/automatonreader.cpp \
    src/automatonsregister.cpp \
    src/filereader.cpp

HEADERS  += \
    src/finitestateautomaton.h \
    src/mainwindow.h \
    src/state.h \
    src/automatonreader.h \
    src/automatonsregister.h \
    src/filereader.h

FORMS    += \
    src/mainwindow.ui
