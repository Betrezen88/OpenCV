#-------------------------------------------------
#
# Project created by QtCreator 2018-03-20T15:37:58
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiceRecognizer
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc

SOURCES += main.cpp\
        MainWindow.cpp \
    CVImageWidget.cpp \
    ContrastEnhancement.cpp \
    PropertiesDialog.cpp \
    ImageProcessor.cpp \
    Recognizer.cpp \
    Dice.cpp

HEADERS  += MainWindow.h \
    CVImageWidget.h \
    ContrastEnhancement.h \
    PropertiesDialog.h \
    ImageProcessor.h \
    Recognizer.h \
    Dice.h
