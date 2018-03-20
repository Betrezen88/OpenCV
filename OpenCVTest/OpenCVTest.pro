#-------------------------------------------------
#
# Project created by QtCreator 2018-03-19T15:37:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVTest
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        Dialog.cpp \
    CVImageWidget.cpp

HEADERS  += Dialog.h \
    CVImageWidget.h
