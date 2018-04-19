#include "Player.h"

#include <QDebug>

Player::Player(const Properties* properties)
    : m_properties(properties)
{
    m_worker.reset( new ImageProcessor(m_properties) );
    stop();
    m_pause = false;
}

void Player::setFilePath(const QString &filePath)
{
    if ( filePath != m_filePath )
        m_filePath = filePath;
}

QString Player::filePath() const
{
    return m_filePath;
}

void Player::stop()
{
    m_stop = true;
    terminate();
    wait();
}

void Player::setLoop(bool l)
{
    m_loop = l;
}

void Player::nextFrame()
{
    if ( !isPaused() )
        pause();

    if ( readNonEmptyFrame(m_frame) )
        processFrame( m_frame );
}

void Player::previousFrame()
{
    if ( !isPaused() )
        pause();

    m_capture.set( CV_CAP_PROP_POS_FRAMES, m_capture.get(CV_CAP_PROP_POS_FRAMES)-2.0 );
    if ( readNonEmptyFrame(m_frame) )
        processFrame( m_frame );
}

bool Player::isStopped()
{
    return m_stop;
}

bool Player::isPaused()
{
    return m_pause;
}

void Player::play()
{
    if ( !isRunning() )
    {
        if ( isStopped() )
            m_stop = false;
        start(LowPriority);
    }
    m_pause = false;
}

void Player::pause()
{
    m_pause = true;
}

void Player::run()
{
    m_capture.open( m_filePath.toStdString() );
    if ( m_capture.isOpened() )
    {
        int delay = ( 1000 / static_cast<int>(m_capture.get(CV_CAP_PROP_FPS)) );
        m_totalFrameCount = static_cast<int>( m_capture.get(CV_CAP_PROP_FRAME_COUNT) );
        emit totalFrameCount( m_totalFrameCount );
        emit singleImage( m_totalFrameCount == 1 );

        while ( !isStopped() )
        {
            if ( !isPaused() )
            {
                if ( !m_capture.read(m_frame) )
                {
                    if ( !m_loop )
                        stop();
                    else
                        m_capture.open( m_filePath.toStdString() );
                }

                if ( !m_frame.empty() )
                    processFrame( m_frame );
                msleep( delay );
            }
            else
                processFrame( m_frame );
        }
    }
}

bool Player::readNonEmptyFrame(cv::Mat &frame)
{
    if ( m_capture.read(frame) )
        if ( !m_frame.empty() )
            return true;
    return false;
}

void Player::processFrame(const cv::Mat &frame)
{
    emit currentFrameNumber( static_cast<int>(m_capture.get(CV_CAP_PROP_POS_FRAMES)) );
    emit resultReady( m_worker->processImage(frame) );
}
