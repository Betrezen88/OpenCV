#include "MainWindow.h"

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QTabWidget>
#include <QThread>
#include <QVBoxLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_tabs( new QTabWidget(this) ),
      m_input( new ImageWidget(this) ),
      m_gray( new ImageWidget(this) ),
      m_threshold( new ImageWidget(this) ),
      m_filter( new ImageWidget(this) ),
      m_output( new ImageWidget(this) ),
      m_playerControls( new PlayerControls(this) )
{
    createActions();
    createMenu();

    m_tabs->addTab( m_input, tr("Input") );
    m_tabs->addTab( m_gray, tr("Gray") );
    m_tabs->addTab( m_threshold, tr("Threshold") );
    m_tabs->addTab( m_filter, tr("Filter") );
    m_tabs->addTab( m_output, tr("Output") );

    QWidget* widget = new QWidget( this );

    QVBoxLayout* all = new QVBoxLayout;
    all->addWidget( m_playerControls );
    all->addWidget( m_tabs );

    widget->setLayout( all );

    setCentralWidget( widget );

    setMinimumSize( 400, 300 );
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    m_filePath.clear();
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "");
    if ( !m_filePath.isEmpty() )
    {
        if ( m_worker == nullptr ) m_worker = new Player();
        if ( m_thread == nullptr ) m_thread = new QThread;

        if ( !m_worker->isWorking() )
        {
            m_worker->setFilePath( m_filePath );
            setConnections( m_thread, m_worker );
            m_worker->moveToThread( m_thread );
            m_thread->start();
        }
    }
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

void MainWindow::setConnections(QThread *thread, Player *worker)
{
    connect( m_playerControls, &PlayerControls::stop,       worker, &Player::stop, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::play,       worker, &Player::play, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::pause,      worker, &Player::pause, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::next,       worker, &Player::next, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::previous,   worker, &Player::previous, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::loop,       worker, &Player::loop, Qt::DirectConnection );

    connect( thread, &QThread::started,     worker, &Player::process, Qt::DirectConnection );
    connect( worker, &Player::finished,     thread, &QThread::quit, Qt::DirectConnection );
    connect( worker, &Player::finished,     worker, &Player::deleteLater, Qt::DirectConnection );
    connect( thread, &QThread::finished,    thread, &QThread::deleteLater, Qt::DirectConnection );
}

