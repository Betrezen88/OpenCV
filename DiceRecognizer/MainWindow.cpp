#include "MainWindow.h"

#include "CVImageWidget.h"
#include "ContrastEnhancement.h"

#include <opencv2/opencv.hpp>

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "");

    cv::Mat cvImage = cv::imread(fileName.toStdString());

    // Poniższy proces przenieść do osobnej klasy rozdzielonej na konkretne kroki
    cv::Mat cvGray;
    cv::Mat cvEnhanced;
    cv::Mat cvThresholded;
    cv::Mat cvFiltrated;

    cv::cvtColor(cvImage, cvGray, CV_BGR2GRAY); // Convert input image to gray

    CVImageWidget* inputImage = new CVImageWidget(this);
    inputImage->showImage(cvImage);

    CVImageWidget* grayImage = new CVImageWidget(this);
    grayImage->showImage(cvGray);

    cvEnhanced = ContrastEnhancement(cvGray, 60.0/50.0).image(); // Enhance gray image

    CVImageWidget* enhancedImage = new CVImageWidget(this);
    enhancedImage->showImage(cvEnhanced);

    cv::threshold(cvGray, cvThresholded, 172, 255, CV_THRESH_BINARY);

    CVImageWidget* thresholdedImage = new CVImageWidget(this);
    thresholdedImage->showImage(cvThresholded);

    cv::dilate(cvThresholded, cvFiltrated, cv::Mat(), cv::Point(-1, -1), 2);
    cv::erode(cvFiltrated, cvFiltrated, cv::Mat(), cv::Point(-1, -1), 1);

    CVImageWidget* filtratedImage = new CVImageWidget(this);
    filtratedImage->showImage(cvFiltrated);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(inputImage, tr("Input Image"));
    m_tabWidget->addTab(grayImage, tr("Gray Image"));
    m_tabWidget->addTab(enhancedImage, tr("Enhanced Image"));
    m_tabWidget->addTab(thresholdedImage, tr("Enhanced Image"));
    m_tabWidget->addTab(filtratedImage, tr("Filtrated Image"));

    setCentralWidget(m_tabWidget);
}

void MainWindow::createMenus()
{
    QAction* openImageAct = new QAction(tr("Open image"), this);
    connect(openImageAct, &QAction::triggered, this, &MainWindow::openImage);

    QMenu* file = menuBar()->addMenu(tr("File"));
    file->addAction(openImageAct);
}
