#-------------------------------------------------
#
# Project created by QtCreator 2016-04-09T21:19:59
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Application
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    studentswindow.cpp \
    addstudentwindow.cpp \
    groupswindow.cpp

HEADERS  += mainwindow.h \
    studentswindow.h \
    addstudentwindow.h \
    groupswindow.h

FORMS    += mainwindow.ui \
    studentswindow.ui \
    addstudentwindow.ui \
    groupswindow.ui

DISTFILES +=
