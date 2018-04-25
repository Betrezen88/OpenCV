#include "Player.h"

#include <QThread>

#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent),
      m_state( State::STOP ),
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
    while ( m_state != State::STOP )
    {
        if ( m_state != State::PAUSE )
        {
            if ( m_loop )
                qDebug() << "Loop video !";
            qDebug() << "processing !";
            QThread::currentThread()->msleep( 1000 );
        }
    }
}

void Player::stop()
{
    m_state = State::STOP;
    emit stateChanged( m_state );
}

void Player::play()
{
    m_state = State::PLAY;
    emit stateChanged( m_state );

    process();
}

void Player::pause()
{
    m_state = State::PAUSE;
    emit stateChanged( m_state );
}

void Player::next()
{
    m_state = State::PAUSE;
}

void Player::previous()
{
    m_state = State::PAUSE;
}

void Player::loop(const bool l)
{
    if ( l != m_loop )
        m_loop = l;
}
