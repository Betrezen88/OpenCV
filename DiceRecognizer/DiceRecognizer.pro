#-------------------------------------------------
#
# Project created by QtCreator 2018-04-23T10:58:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiceRecognizer
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio

SOURCES += main.cpp\
        MainWindow.cpp \
        ImageWidget.cpp \
    PlayerControls.cpp \
    Player.cpp \
    Properties.cpp \
    ImageProcessor.cpp \
    Dice.cpp

HEADERS  += MainWindow.h \
        ImageWidget.h \
    PlayerControls.h \
    Player.h \
    Properties.h \
    ImageProcessor.h \
    Dice.h
