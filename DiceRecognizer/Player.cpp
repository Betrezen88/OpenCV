#include "Player.h"

#include <QThread>

#include <QDebug>

Player::Player(QObject *parent)
    : QObject(parent),
      m_stop(false),
      m_pause(false),
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

bool Player::isWorking() const
{
    return m_working;
}

void Player::process()
{
    m_working = true;
    while ( !m_stop )
    {
        if ( !m_pause )
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
