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
    groupswindow.cpp \
    addgroupwindow.cpp \
    editgroupwindow.cpp \
    addstudenttogroup.cpp \
    markswindow.cpp \
    addmarkwindow.cpp \
    addevent.cpp

HEADERS  += mainwindow.h \
    studentswindow.h \
    addstudentwindow.h \
    groupswindow.h \
    addgroupwindow.h \
    editgroupwindow.h \
    addstudenttogroup.h \
    markswindow.h \
    addmarkwindow.h \
    addevent.h

FORMS    += mainwindow.ui \
    studentswindow.ui \
    addstudentwindow.ui \
    groupswindow.ui \
    addgroupwindow.ui \
    editgroupwindow.ui \
    addstudenttogroup.ui \
    markswindow.ui \
    addmarkwindow.ui \
    addevent.ui

DISTFILES +=
