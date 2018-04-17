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
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio

SOURCES += main.cpp\
        MainWindow.cpp \
    ImageProcessor.cpp \
    ImageWigdet.cpp \
    Dice.cpp \
    Recognizer.cpp \
    Properties.cpp \
    Player.cpp \
    PlayerControls.cpp

HEADERS  += MainWindow.h \
    ImageProcessor.h \
    ImageWigdet.h \
    Dice.h \
    Recognizer.h \
    Properties.h \
    Player.h \
    PlayerControls.h
