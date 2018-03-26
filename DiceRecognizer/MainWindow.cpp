#include "MainWindow.h"

#include "CVImageWidget.h"
#include "ContrastEnhancement.h"

#include <opencv2/opencv.hpp>
#include <opencv/highgui.h>

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_propsDialog = new PropertiesDialog(this);
    m_imgProc = new ImageProcessor(*m_propsDialog);

    m_inputImage = new CVImageWidget(this);
    m_grayImage = new CVImageWidget(this);
    m_thresholdedImage = new CVImageWidget(this);
    m_filteredImage = new CVImageWidget(this);
    m_outputImage = new CVImageWidget(this);

    connect(m_imgProc, &ImageProcessor::finished, this, &MainWindow::refreashImages);

    m_propsDialog->setContrast(60);
    m_propsDialog->setThreshold(172);
    m_propsDialog->setDilation(2);
    m_propsDialog->setErosion(1);
    m_propsDialog->setDiceSize(25);
    m_propsDialog->setDotSize(3);

    createMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "");

    //cv::Mat cvImage;// = cv::imread(fileName.toStdString());

    cv::VideoCapture cvVideo;
    cvVideo.open(fileName.toStdString());

    m_imgProc->process(cvVideo);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(m_inputImage, tr("Input Image"));
    m_tabWidget->addTab(m_grayImage, tr("Gray Image"));
    m_tabWidget->addTab(m_thresholdedImage, tr("Thresholed Image"));
    m_tabWidget->addTab(m_filteredImage, tr("Filtrated Image"));
    m_tabWidget->addTab(m_outputImage, tr("Output Image"));

    setCentralWidget(m_tabWidget);
}

void MainWindow::openPropsDialog()
{
    m_propsDialog->show();
}

void MainWindow::refreashImages()
{
    m_inputImage->showImage(m_imgProc->inputImage());
    m_grayImage->showImage(m_imgProc->grayImage());
    m_thresholdedImage->showImage(m_imgProc->thresholdedImage());
    m_filteredImage->showImage(m_imgProc->filteredImage());
    m_outputImage->showImage(m_imgProc->outputImage());
}

void MainWindow::createMenus()
{
    QAction* openImageAct = new QAction(tr("Open image"), this);
    connect(openImageAct, &QAction::triggered, this, &MainWindow::openImage);

    QAction* openProps = new QAction(tr("Properties"));
    connect(openProps, &QAction::triggered, this, &MainWindow::openPropsDialog);

    QMenu* file = menuBar()->addMenu(tr("File"));
    file->addAction(openImageAct);
    file->addAction(openProps);
}
