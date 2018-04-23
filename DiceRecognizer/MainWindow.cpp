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

bool MainWindow::openFile()
{
    return true;
}

void MainWindow::createActions()
{
    m_openFileAct = new QAction( tr("Open File"), this );
    m_quitAct = new QAction( tr("Quit"), this );

    connect( m_openFileAct, &QAction::triggered, this, &MainWindow::openFile );
    connect( m_quitAct, &QAction::triggered, this, &MainWindow::close );
}

void MainWindow::createMenu()
{
    m_fileMenu = menuBar()->addMenu( tr("File") + "..." );

    m_fileMenu->addAction( m_openFileAct );
    m_fileMenu->addAction( m_quitAct );
}
