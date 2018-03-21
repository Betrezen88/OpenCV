#include "MainWindow.h"

#include "CVImageWidget.h"

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
    cv::Mat cvGray;

    cv::cvtColor(cvImage, cvGray, CV_BGR2GRAY);

    CVImageWidget* inputImage = new CVImageWidget(this);
    inputImage->showImage(cvImage);

    CVImageWidget* grayImage = new CVImageWidget(this);
    grayImage->showImage(cvGray);

    m_tabWidget = new QTabWidget(this);
    m_tabWidget->addTab(inputImage, tr("Input Image"));
    m_tabWidget->addTab(grayImage, tr("Gray Image"));

    setCentralWidget(m_tabWidget);
}

void MainWindow::createMenus()
{
    QAction* openImageAct = new QAction(tr("Open image"), this);
    connect(openImageAct, &QAction::triggered, this, &MainWindow::openImage);

    QMenu* file = menuBar()->addMenu(tr("File"));
    file->addAction(openImageAct);
}
