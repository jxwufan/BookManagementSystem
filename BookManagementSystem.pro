#-------------------------------------------------
#
# Project created by QtCreator 2015-03-19T18:07:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookManagmentSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    connection.h

FORMS    += mainwindow.ui \
    logindialog.ui

QT += sql
