#include "Player.h"

#include <QThread>

#include <QDebug>

Player::Player(const Properties *properties, QObject *parent)
    : QObject(parent),
      m_properties( properties ),
      m_imgProc( new ImageProcessor(m_properties) ),
      m_stop(false),
      m_pause(true),
      m_loop( false )
{

}

Player::~Player()
{
    qDebug() << "Player destroyed !";
}

void Player::setFilePath(const QString &filePath)
{
    if ( filePath != m_filePath )
        m_filePath = filePath;
}

const QString Player::filePath() const
{
    return m_filePath;
}

void Player::process()
{
    qDebug() << "Player::process()";
    m_capture.open( m_filePath.toStdString() );
    if ( m_capture.isOpened() )
    {
        m_delay = ( 1000 / static_cast<int>(m_capture.get(CV_CAP_PROP_FPS)) );
        emit newFrameCount( static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_COUNT)) );

        while ( true )
        {
            if ( !m_stop && !m_pause )
            {
                if ( !m_capture.read( m_frame ) )
                {
                    if ( !m_loop )
                        stop();
                    else
                        m_capture.open( m_filePath.toStdString() );
                }
                if ( !m_frame.empty() )
                {
                    processImage( m_frame );
                    QThread::currentThread()->msleep( m_delay );
                }
            }
        }
    }
}

void Player::stop()
{
    qDebug() << "Player::stop()";
    m_stop = true;
    m_capture.set( CV_CAP_PROP_POS_FRAMES, 0 );
}

void Player::play()
{
    qDebug() << "Player::play()";
    m_stop = false;
    m_pause = false;
}

void Player::pause()
{
    qDebug() << "Player::pause()";
    m_pause = true;
}

void Player::next()
{
    if ( !m_pause ) m_pause = true;

    if ( readNonEmptyFrame(m_frame) )
        processImage( m_frame );
}

void Player::previous()
{
    if ( !m_pause ) m_pause = true;

    m_capture.set( CV_CAP_PROP_POS_FRAMES, m_capture.get(CV_CAP_PROP_POS_FRAMES)-2.0 );
    if ( readNonEmptyFrame(m_frame) )
        processImage( m_frame );
}

void Player::loop(const bool l)
{
    if ( l != m_loop )
        m_loop = l;
}

void Player::processImage(const cv::Mat &img)
{
    emit newCurrentFrameNumber( static_cast<int>(m_capture.get(CV_CAP_PROP_POS_FRAMES)) );
    emit resultReady( m_imgProc->processImage(img) );
}

bool Player::readNonEmptyFrame(const cv::Mat &frame)
{
    if ( m_capture.read(frame) )
        if ( !m_frame.empty() )
            return true;
    return false;
}
