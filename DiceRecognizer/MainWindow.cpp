#include "MainWindow.h"

#include <QAction>
#include <QMenu>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createMenu();
}

MainWindow::~MainWindow()
{

}

void MainWindow::openImage()
{

}

void MainWindow::createMenu()
{
    m_fileMenu = menuBar()->addMenu( tr("File") );

    m_fileMenu->addAction( m_openImageAct );
}

void MainWindow::createActions()
{
    m_openImageAct = new QAction( tr("Open Image") + "..." );

    connect( m_openImageAct, &QAction::triggered, this, &MainWindow::openImage );
}
