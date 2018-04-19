#include "PlayerControls.h"

#include <QCheckBox>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

#include <QHBoxLayout>

#include <QDebug>

PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent),
      m_stop( new QPushButton("[]", this) ),
      m_pause( new QPushButton("||", this) ),
      m_play( new QPushButton(">", this) ),
      m_previous( new QPushButton("<<", this) ),
      m_next( new QPushButton(">>", this) ),
      m_loop( new QCheckBox("Loop", this) ),
      m_time( new QSlider(Qt::Horizontal, this) ),
      m_timeLabel( new QLabel("0 / 0", this) )
{
    connect( m_stop, &QPushButton::clicked, this, &PlayerControls::stop );
    connect( m_play, &QPushButton::clicked, this, &PlayerControls::play );
    connect( m_pause, &QPushButton::clicked, this, &PlayerControls::pause );
    connect( m_previous, &QPushButton::clicked, this, &PlayerControls::previous );
    connect( m_next, &QPushButton::clicked, this, &PlayerControls::next );
    connect( m_loop, &QCheckBox::clicked, this, &PlayerControls::loop );

    QHBoxLayout* all = new QHBoxLayout;
    all->addWidget( m_previous );
    all->addWidget( m_stop );
    all->addWidget( m_pause );
    all->addWidget( m_play );
    all->addWidget( m_next );
    all->addWidget( m_time );
    all->addWidget( m_timeLabel );
    all->addWidget( m_loop );

    setLayout( all );
}

void PlayerControls::setTotalTime(int t)
{
    m_time->setRange(0, t);
    m_timeLabel->setText( QString("0 / %1").arg(t) );
}

void PlayerControls::setCurrentTime(int t)
{
    m_time->setValue( t );
    m_timeLabel->setText( QString("%1 / %2").arg(t).arg(m_time->maximum()) );
}

void PlayerControls::disableControls(bool y)
{
    m_stop->setDisabled( y );
    m_pause->setDisabled( y );
    m_previous->setDisabled( y );
    m_next->setDisabled( y );
}
