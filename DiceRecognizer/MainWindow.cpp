#include "MainWindow.h"

#include <opencv2/opencv.hpp>

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QTabWidget>
#include <QThread>
#include <QVBoxLayout>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_tabWidget( new QTabWidget(this) ),
      m_input( new ImageWidget(this) ),
      m_gray( new ImageWidget(this) ),
      m_threshold( new ImageWidget(this) ),
      m_filter( new ImageWidget(this) ),
      m_output( new ImageWidget(this) ),
      m_properties( new Properties(this) ),
      m_player( new Player(m_properties) ),
      m_playerControlls( new PlayerControls(this) )
{
    createActions();
    createMenu();

    qRegisterMetaType< QVector<cv::Mat> >( "QVector<cv::Mat>" );

    connect( m_playerControlls, &PlayerControls::play, this, &MainWindow::play );
    connect( m_playerControlls, &PlayerControls::pause, m_player, &Player::pause );
    connect( m_playerControlls, &PlayerControls::stop, m_player, &Player::stop );
    connect( m_playerControlls, &PlayerControls::loop, m_player, &Player::setLoop );
    connect( m_player, &Player::resultReady, this, &MainWindow::updateImages );
    connect( m_player, &Player::totalFrameCount, m_playerControlls, &PlayerControls::setTotalTime );
    connect( m_player, &Player::currentFrameNumber, m_playerControlls, &PlayerControls::setCurrentTime );

    m_properties->setContrast( 60 );
    m_properties->setThreshold( 172 );
    m_properties->setDilatation( 2 );
    m_properties->setErosion( 1 );

    m_tabWidget->addTab( m_input, tr("Input") );
    m_tabWidget->addTab( m_gray, tr("Gray") );
    m_tabWidget->addTab( m_threshold, tr("Threshold") );
    m_tabWidget->addTab( m_filter, tr("Filter") );
    m_tabWidget->addTab( m_output, tr("Output") );

    setMinimumSize( 400, 300 );

    QVBoxLayout* all = new QVBoxLayout;
    all->addWidget( m_playerControlls );
    all->addWidget( m_tabWidget );

    QWidget* central = new QWidget(this);
    central->setLayout( all );

    setCentralWidget( central );
}

MainWindow::~MainWindow()
{
    if ( m_player->isRunning() )
    {
        m_player->stop();
        m_player->quit();
    }
}

void MainWindow::openImage()
{
    openFile();
}

void MainWindow::showProperties()
{
    m_properties->show();
}

void MainWindow::displayError(const QString message)
{
    QMessageBox::warning(this, tr("Warning"), message, QMessageBox::Ok);
}

void MainWindow::updateImages(const QVector<cv::Mat> images)
{
    m_input->showImage( images.at(0) );
    m_gray->showImage( images.at(1) );
    m_threshold->showImage( images.at(2) );
    m_filter->showImage( images.at(3) );
    m_output->showImage( images.at(4) );
}

void MainWindow::play()
{
    if ( m_player->filePath().isEmpty() )
        if ( !openFile() )
            return;
    m_player->play();
}

void MainWindow::createMenu()
{
    m_fileMenu = menuBar()->addMenu( tr("File") );

    m_fileMenu->addAction( m_openImageAct );
    m_fileMenu->addAction( m_showPropertiesAct );
}

void MainWindow::createActions()
{
    m_openImageAct = new QAction( tr("Open Image") + "..." );

    connect( m_openImageAct, &QAction::triggered, this, &MainWindow::openImage );

    m_showPropertiesAct = new QAction( tr("Show Properties") + "..." );

    connect( m_showPropertiesAct, &QAction::triggered, this, &MainWindow::showProperties );
}

bool MainWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "");
    m_player->setFilePath( filePath );
    return !filePath.isEmpty();
}
