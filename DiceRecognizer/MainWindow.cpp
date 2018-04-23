#include "MainWindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_tabs( new QTabWidget(this) ),
      m_input( new ImageWidget(this) ),
      m_gray( new ImageWidget(this) ),
      m_threshold( new ImageWidget(this) ),
      m_filter( new ImageWidget(this) ),
      m_output( new ImageWidget(this) )
{
    createActions();
    createMenu();

    m_tabs->addTab( m_input, tr("Input") );
    m_tabs->addTab( m_gray, tr("Gray") );
    m_tabs->addTab( m_threshold, tr("Threshold") );
    m_tabs->addTab( m_filter, tr("Filter") );
    m_tabs->addTab( m_output, tr("Output") );

    setCentralWidget( m_tabs );

    setMinimumSize( 400, 300 );
}

MainWindow::~MainWindow()
{

}

bool MainWindow::openFile()
{
    m_filePath.clear();
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "");
    if ( m_filePath.isEmpty() )
        return false;
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
