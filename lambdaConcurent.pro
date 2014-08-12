#-------------------------------------------------
#
# Project created by QtCreator 2013-04-28T16:00:00
#  Author: Gerasymchuk Nazar
#  neval8.wordpress.com
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lambdaConcurent
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    dao.cpp \
    threaddao.cpp \
    QProgressIndicator.cpp

HEADERS  += mainwindow.h \
    dao.h \
    sleeperthread.h \
    threaddao.h \
    QProgressIndicator.h

FORMS    += mainwindow.ui

# for supporting new standard
QMAKE_CXXFLAGS += -std=c++11

# for static analisys
#QMAKE_CXXFLAGS += -isystem "/usr/local/Trolltech/Qt-4.8.4/include"
#QMAKE_CXXFLAGS += -Wall -Wextra -pedantic

