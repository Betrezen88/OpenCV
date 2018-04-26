#include "Player.h"

#include <QThread>

#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent),
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

        while ( !m_stop )
        {
            if ( !m_pause )
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
                    emit resultReady( m_frame );
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
    emit finished();
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
    m_pause = true;
}

void Player::previous()
{
    m_pause = true;
}

void Player::loop(const bool l)
{
    if ( l != m_loop )
        m_loop = l;
}
