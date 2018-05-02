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
      m_properties( new Properties(this) )
{
    createActions();
    createMenu();

    m_playerControls->disable( true );

    m_properties->setContrast( 60 );
    m_properties->setThreshold( 172 );
    m_properties->setDilatation( 2 );
    m_properties->setErosion( 1 );
    m_properties->setDiceSize( 25 );
    m_properties->setDotSize( 3 );

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
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), "", "");
    if ( !filePath.isEmpty() )
    {
        if ( m_thread.isNull() )
        {
            m_player.reset( new Player(m_properties) );
            m_thread.reset( new QThread );
            setConnections( m_thread.data(), m_player.data() );
            m_player->moveToThread( m_thread.data() );
            m_thread->start();
        }
        m_player->setFilePath( filePath );
    }
}

void MainWindow::openProperties()
{
    m_properties->show();
}

void MainWindow::clean()
{
    if ( !m_thread.isNull() )
    {
        m_player.reset();
        QThread* tmp = m_thread.take();
        tmp->quit();
        tmp->deleteLater();
    }
}

void MainWindow::updateImages(const QHash<QString, cv::Mat> images)
{
    m_input->showImage( images.value("input") );
    m_gray->showImage( images.value("gray") );
    m_threshold->showImage( images.value("threshold") );
    m_filter->showImage( images.value("filter") );
    m_output->showImage( images.value("output") );
}

void MainWindow::updateSize(const int& width, const int& height)
{
    resize( width + 25, height + m_playerControls->height() + 70 );
}

void MainWindow::createActions()
{
    m_openFileAct = new QAction( tr("Open File"), this );
    m_openPropertiesAct = new QAction( tr("Open Properties"), this);
    m_quitAct = new QAction( tr("Quit"), this );

    connect( m_openFileAct, &QAction::triggered, this, &MainWindow::openFile );
    connect( m_openPropertiesAct, &QAction::triggered, this, &MainWindow::openProperties );
    connect( m_quitAct, &QAction::triggered, this, &MainWindow::close );
}

void MainWindow::createMenu()
{
    m_fileMenu = menuBar()->addMenu( tr("File") + "..." );

    m_fileMenu->addAction( m_openFileAct );
    m_fileMenu->addAction( m_openPropertiesAct );
    m_fileMenu->addAction( m_quitAct );
}

void MainWindow::setConnections(QThread *thread, Player *worker)
{
    qRegisterMetaType<QHash<QString, cv::Mat>>("QHash<QString, cv::Mat>");

    connect( m_playerControls, &PlayerControls::stop,       worker, &Player::stop, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::play,       worker, &Player::play, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::pause,      worker, &Player::pause, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::next,       worker, &Player::next, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::previous,   worker, &Player::previous, Qt::DirectConnection );
    connect( m_playerControls, &PlayerControls::loop,       worker, &Player::loop, Qt::DirectConnection );

    connect( worker, &Player::newFrameCount, m_playerControls, &PlayerControls::updateFrameCount, Qt::DirectConnection );
    connect( worker, &Player::newCurrentFrameNumber, m_playerControls, &PlayerControls::updateCurrentFrameNumber, Qt::DirectConnection );
    connect( worker, &Player::newSize, this, &MainWindow::updateSize );
    connect( worker, &Player::singleImage, m_playerControls, &PlayerControls::disable, Qt::DirectConnection );

    connect( thread, &QThread::started,     worker, &Player::process, Qt::DirectConnection );
    connect( worker, &Player::resultReady,  this, &MainWindow::updateImages, Qt::DirectConnection );
    connect( worker, &Player::finished,     thread, &QThread::quit, Qt::DirectConnection );
    connect( worker, &Player::finished,     worker, &Player::deleteLater, Qt::DirectConnection );
    connect( thread, &QThread::finished,    this, &MainWindow::clean, Qt::DirectConnection );
}

void MainWindow::disconnectPointers(QThread *thread, Player *worker)
{
    disconnect( m_playerControls, &PlayerControls::stop,       worker, &Player::stop );
    disconnect( m_playerControls, &PlayerControls::play,       worker, &Player::play );
    disconnect( m_playerControls, &PlayerControls::pause,      worker, &Player::pause );
    disconnect( m_playerControls, &PlayerControls::next,       worker, &Player::next );
    disconnect( m_playerControls, &PlayerControls::previous,   worker, &Player::previous );
    disconnect( m_playerControls, &PlayerControls::loop,       worker, &Player::loop );

    disconnect( worker, &Player::newFrameCount, m_playerControls, &PlayerControls::updateFrameCount );
    disconnect( worker, &Player::newCurrentFrameNumber, m_playerControls, &PlayerControls::updateCurrentFrameNumber );
    disconnect( worker, &Player::newSize, this, &MainWindow::updateSize );
    disconnect( worker, &Player::singleImage, m_playerControls, &PlayerControls::disable );

    disconnect( thread, &QThread::started,     worker, &Player::process );
    disconnect( worker, &Player::resultReady,  this, &MainWindow::updateImages );
    disconnect( worker, &Player::finished,     thread, &QThread::quit );
    disconnect( worker, &Player::finished,     worker, &Player::deleteLater );
    disconnect( thread, &QThread::finished,    this, &MainWindow::clean );
}
