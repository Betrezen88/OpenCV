#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "PropertiesDialog.h"
#include "ImageProcessor.h"

class QTabWidget;
class CVImageWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openImage();
    void openPropsDialog();
    void refreashImages();

private:
    void createMenus();

private:
    QTabWidget* m_tabWidget;
    PropertiesDialog* m_propsDialog;
    ImageProcessor* m_imgProc;

    CVImageWidget* m_inputImage;
    CVImageWidget* m_grayImage;
    CVImageWidget* m_thresholdedImage;
    CVImageWidget* m_filteredImage;
    CVImageWidget* m_outputImage;
};

#endif // MAINWINDOW_H
