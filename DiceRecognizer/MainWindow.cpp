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
      m_playerControls( new PlayerControls(this) ),
      m_exists( false )
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
    clean();
}

void MainWindow::openFile()
{
    m_filePath.clear();
    m_filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "");
    if ( !m_filePath.isEmpty() )
    {
        if ( m_thread.isNull() )
        {
            m_player.reset( new Player() );
            m_thread.reset( new QThread );

            m_player->setFilePath( m_filePath );
            setConnections( m_thread.data(), m_player.data() );
            m_player->moveToThread( m_thread.data() );
            m_thread->start();

        }
        else
            m_player->setFilePath( m_filePath );
    }
}

void MainWindow::clean()
{
    m_player.reset();
    if ( !m_thread.isNull() )
    {
        QThread* tmp = m_thread.take();
        tmp->deleteLater();
    }
}

void MainWindow::updateImages(const cv::Mat img)
{
    m_input->showImage( img );
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
    connect( worker, &Player::resultReady,  this, &MainWindow::updateImages, Qt::DirectConnection );
    connect( worker, &Player::finished,     thread, &QThread::quit, Qt::DirectConnection );
    connect( worker, &Player::finished,     worker, &Player::deleteLater, Qt::DirectConnection );
    connect( thread, &QThread::finished,    this, &MainWindow::clean, Qt::DirectConnection );
}
