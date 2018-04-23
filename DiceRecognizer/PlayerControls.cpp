#include "PlayerControls.h"

#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QHBoxLayout>

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
