#include "Properties.h"

#include <QLabel>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>

Properties::Properties(QWidget *parent)
    : QDialog(parent),
      m_contrast(new QSpinBox(this)),
      m_threshold(new QSpinBox(this)),
      m_dilatation(new QSpinBox(this)),
      m_erosion(new QSpinBox(this))
{
    m_contrast->setRange( 0, 100 );
    m_threshold->setRange( 0, 255 );
    m_dilatation->setRange( 0, 50 );
    m_erosion->setRange( 0, 50 );

    QSlider* contrast = new QSlider(Qt::Horizontal, this);
    QSlider* threshold = new QSlider(Qt::Horizontal, this);
    QSlider* dilatation = new QSlider(Qt::Horizontal, this);
    QSlider* erosion = new QSlider(Qt::Horizontal, this);

    contrast->setRange( m_contrast->minimum(), m_contrast->maximum() );
    threshold->setRange( m_threshold->minimum(), m_threshold->maximum() );
    dilatation->setRange( m_dilatation->minimum(), m_dilatation->maximum() );
    erosion->setRange( m_erosion->minimum(), m_erosion->maximum() );

    connect( m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), contrast, &QSlider::setValue );
    connect( m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), threshold, &QSlider::setValue );
    connect( m_dilatation, QOverload<int>::of(&QSpinBox::valueChanged), dilatation, &QSlider::setValue );
    connect( m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), erosion, &QSlider::setValue );

    connect( contrast, &QSlider::valueChanged, m_contrast, &QSpinBox::setValue );
    connect( threshold, &QSlider::valueChanged, m_threshold, &QSpinBox::setValue );
    connect( dilatation, &QSlider::valueChanged, m_dilatation, &QSpinBox::setValue );
    connect( erosion, &QSlider::valueChanged, m_erosion, &QSpinBox::setValue );

    connect( m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), [=](){ emit valueChanged(); } );
    connect( m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), [=](){ emit valueChanged(); } );
    connect( m_dilatation, QOverload<int>::of(&QSpinBox::valueChanged), [=](){ emit valueChanged(); } );
    connect( m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), [=](){ emit valueChanged(); } );

    QGridLayout* all = new QGridLayout;
    all->addWidget( new QLabel(tr("Contrast"), this), 0, 0 );
    all->addWidget( m_contrast, 0, 1 );
    all->addWidget( contrast, 0, 2 );
    all->addWidget( new QLabel(tr("Threshold"), this), 1, 0 );
    all->addWidget( m_threshold, 1, 1 );
    all->addWidget( threshold, 1, 2 );
    all->addWidget( new QLabel(tr("Dilatation"), this), 2, 0 );
    all->addWidget( m_dilatation, 2, 1 );
    all->addWidget( dilatation, 2, 2 );
    all->addWidget( new QLabel(tr("Erosion"), this), 3, 0 );
    all->addWidget( m_erosion, 3, 1 );
    all->addWidget( erosion, 3, 2 );

    setLayout( all );
}

void Properties::setContrast(const int c)
{
    if ( m_contrast->value() != c )
    {
        m_contrast->setValue( c );
        emit valueChanged();
    }
}

void Properties::setThreshold(const int t)
{
    if ( m_threshold->value() != t )
    {
        m_threshold->setValue( t );
        emit valueChanged();
    }
}

void Properties::setDilatation(const int d)
{
    if ( m_dilatation->value() != d )
    {
        m_dilatation->setValue( d );
        emit valueChanged();
    }
}

void Properties::setErosion(const int e)
{
    if ( m_erosion->value() != e )
    {
        m_erosion->setValue( e );
        emit valueChanged();
    }
}

int Properties::contrast() const
{
    return m_contrast->value();
}

int Properties::threshold() const
{
    return m_threshold->value();
}

int Properties::dilatation() const
{
    return m_dilatation->value();
}

int Properties::erosion() const
{
    return m_erosion->value();
}
