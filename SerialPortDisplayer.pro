#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T17:57:55
#
#-------------------------------------------------

QMAKE_CXXFLAGS	+= -std=c++11

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SerialPortDisplayer
TEMPLATE = app


SOURCES += main.cpp\
        SerialPortDisplayer.cpp

HEADERS  += SerialPortDisplayer.h
