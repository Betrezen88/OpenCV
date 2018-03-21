#include "MainWindow.h"

#include "CVImageWidget.h"

#include <opencv2/opencv.hpp>

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();

    m_cvWidget = new CVImageWidget(this);
    setCentralWidget(m_cvWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "");

    cv::Mat cvImage = cv::imread(fileName.toStdString());

    m_cvWidget->showImage(cvImage);
}

void MainWindow::createMenus()
{
    QAction* openImageAct = new QAction(tr("Open image"), this);
    connect(openImageAct, &QAction::triggered, this, &MainWindow::openImage);

    QMenu* file = menuBar()->addMenu(tr("File"));
    file->addAction(openImageAct);
}
