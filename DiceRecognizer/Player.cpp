#include "Player.h"

#include <QDebug>

Player::Player(const Properties* properties)
    : m_properties(properties)
{
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
    capture.open( m_filePath.toStdString() );
    if ( capture.isOpened() )
    {
        int delay = ( 1000 / static_cast<int>(capture.get(CV_CAP_PROP_FPS)) );
        m_totalFrameCount = static_cast<int>( capture.get(CV_CAP_PROP_FRAME_COUNT) );
        emit totalFrameCount( m_totalFrameCount );

        cv::Mat frame;
        while ( !isStopped() )
        {
            while ( !isPaused() )
            {
                if ( !capture.read(frame) )
                {
                    if ( !m_loop )
                        stop();
                    else
                        capture.open( m_filePath.toStdString() );
                }

                if ( !frame.empty() )
                {
                    emit currentFrameNumber( static_cast<int>(capture.get(CV_CAP_PROP_POS_FRAMES)) );
                    ImageProcessor worker(m_properties);
                    emit resultReady( worker.processImage(frame) );
                }
                msleep( delay );
            }
        }
    }
}
