#include "Player.h"

#include <QThread>

#include <QDebug>

Player::Player(const Properties *properties, QObject *parent)
    : QObject(parent),
      m_properties( properties ),
      m_imgProc( new ImageProcessor(m_properties) ),
      m_loop( false ),
      m_state( State::IDLE )
{

}

Player::~Player()
{
    emit finished();
}

const QString Player::filePath() const
{
    return m_filePath;
}

void Player::process()
{
     while ( m_state != State::END )
     {
        switch( m_state )
        {
        case State::PLAY:
        {
            if ( m_capture.isOpened() )
            {
                if ( !processNonEmptyFrame() )
                {
                    if ( m_loop )
                        m_capture.open( m_filePath.toStdString() );
                    else
                        stop();
                }
            }
            else
                m_state = State::END;
            break;
        }
        case State::PAUSE:
        {
            processImage( m_frame );
            break;
        }
        case State::NEXT:
        {
            processNonEmptyFrame();
            m_state = State::PAUSE;
            break;
        }
        case State::PREVIOUS:
        {
            m_capture.set( CV_CAP_PROP_POS_FRAMES, m_capture.get(CV_CAP_PROP_POS_FRAMES)-2.0 );
            processNonEmptyFrame();
            m_state = State::PAUSE;
            break;
        }
        case State::STOP:
        {
            resetDisplay();
            break;
        }
        default:
            break;
        }
        QThread::currentThread()->msleep( m_delay );
     }
     emit finished();
}

void Player::stop()
{
    m_state = State::STOP;
}

void Player::play()
{
    m_state = State::PLAY;
}

void Player::pause()
{
    m_state = State::PAUSE;
}

void Player::next()
{
    m_state = State::NEXT;
}

void Player::previous()
{
    m_state = State::PREVIOUS;
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

bool Player::processNonEmptyFrame()
{
    if ( m_capture.read(m_frame) )
        if ( !m_frame.empty() )
        {
            processImage( m_frame );
            return true;
        }
    return false;
}

void Player::resetDisplay()
{
    m_capture.set( CV_CAP_PROP_POS_FRAMES, 0 );
    processNonEmptyFrame();
}

void Player::openFile(const QString filePath)
{
    if ( m_filePath != filePath )
    {
        m_filePath = filePath;
        m_capture.open( m_filePath.toStdString() );
        if ( !m_capture.isOpened() )
            return;

        m_delay = ( 1000 / static_cast<int>(m_capture.get(CV_CAP_PROP_FPS)) );
        emit newFrameCount( static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_COUNT)) );
        emit newSize( static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_WIDTH)), static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_HEIGHT)) );
        emit singleImage( static_cast<int>(m_capture.get(CV_CAP_PROP_FRAME_COUNT)) == 1 );
        resetDisplay();
    }
}
