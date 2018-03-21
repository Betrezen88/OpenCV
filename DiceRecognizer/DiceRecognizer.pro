#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T15:37:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiceRecognizer
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        MainWindow.cpp \
    CVImageWidget.cpp \
    ContrastEnhancement.cpp

HEADERS  += MainWindow.h \
    CVImageWidget.h \
    ContrastEnhancement.h
