#include "PlayerControls.h"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>

#include <QDebug>

PlayerControls::PlayerControls(QWidget *parent)
    : QWidget(parent),
      m_stopBtn( new QPushButton(tr("[]"), this) ),
      m_playBtn( new QPushButton(tr(">"), this) ),
      m_pauseBtn( new QPushButton(tr("||"), this) ),
      m_previousBtn( new QPushButton(tr("<<"), this) ),
      m_nextBtn( new QPushButton(tr(">>"), this) ),
      m_loop( new QCheckBox(tr("loop"), this) ),
      m_time( new QSlider(Qt::Horizontal, this) ),
      m_timeL( new QLabel("--/--") )
{   
    connect( m_stopBtn, &QPushButton::clicked, this, &PlayerControls::stop );
    connect( m_playBtn, &QPushButton::clicked, this, &PlayerControls::play );
    connect( m_pauseBtn, &QPushButton::clicked, this, &PlayerControls::pause );
    connect( m_previousBtn, &QPushButton::clicked, this, &PlayerControls::previous );
    connect( m_nextBtn, &QPushButton::clicked, this, &PlayerControls::next );
    connect( m_loop, &QCheckBox::clicked, this, &PlayerControls::loop );

    QHBoxLayout *all = new QHBoxLayout;
    all->addWidget( m_previousBtn );
    all->addWidget( m_stopBtn );
    all->addWidget( m_pauseBtn );
    all->addWidget( m_playBtn );
    all->addWidget( m_nextBtn );
    all->addWidget( m_timeL );
    all->addWidget( m_time );
    all->addWidget( m_loop );

    setLayout( all );
}

void PlayerControls::updateFrameCount(const int frameCount)
{
    m_time->setRange( 1, frameCount );
    m_timeL->setText( QString("0 / %1").arg(frameCount) );
}
