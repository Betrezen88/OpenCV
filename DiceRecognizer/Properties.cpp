#include "Properties.h"

#include <QLabel>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>

Properties::Properties(QWidget *parent)
    : QDialog(parent),
      m_contrast( new QSpinBox(this) ),
      m_threshold( new QSpinBox(this) ),
      m_dilatation( new QSpinBox(this) ),
      m_erosion( new QSpinBox(this) ),
      m_diceSize( new QSpinBox(this) ),
      m_dotSize( new QSpinBox(this) ),
      m_threasholdType( new QComboBox(this) ),
      m_dilatationFirts( new QRadioButton(tr("Dilatation first"), this) ),
      m_erosionFirst( new QRadioButton(tr("Erosion first"), this) )
{
    m_types << "BINARY" << "BINARY INVERT" << "TRUNC" << "TO ZERO" << "TO ZERO INVERT";
    m_threasholdType->addItems( m_types );

    m_contrast->setRange( 0, 100 );
    m_threshold->setRange( 0, 255 );
    m_dilatation->setRange( 0, 50 );
    m_erosion->setRange( 0, 50 );
    m_diceSize->setRange( 1, 100 );
    m_dotSize->setRange( 1, 100 );

    m_dilatationFirts->setChecked( true );
    m_erosionFirst->setChecked( false );

    QSlider* contrast = new QSlider(Qt::Horizontal, this);
    QSlider* threshold = new QSlider(Qt::Horizontal, this);
    QSlider* dilatation = new QSlider(Qt::Horizontal, this);
    QSlider* erosion = new QSlider(Qt::Horizontal, this);
    QSlider* diceSize = new QSlider(Qt::Horizontal, this);
    QSlider* dotSize = new QSlider(Qt::Horizontal, this);

    contrast->setRange( m_contrast->minimum(), m_contrast->maximum() );
    threshold->setRange( m_threshold->minimum(), m_threshold->maximum() );
    dilatation->setRange( m_dilatation->minimum(), m_dilatation->maximum() );
    erosion->setRange( m_erosion->minimum(), m_erosion->maximum() );
    diceSize->setRange( m_diceSize->minimum(), m_diceSize->maximum() );
    dotSize->setRange( m_dotSize->minimum(), m_dotSize->maximum() );

    connect( m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), contrast, &QSlider::setValue );
    connect( m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), threshold, &QSlider::setValue );
    connect( m_dilatation, QOverload<int>::of(&QSpinBox::valueChanged), dilatation, &QSlider::setValue );
    connect( m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), erosion, &QSlider::setValue );
    connect( m_diceSize, QOverload<int>::of(&QSpinBox::valueChanged), diceSize, &QSlider::setValue );
    connect( m_dotSize, QOverload<int>::of(&QSpinBox::valueChanged), dotSize, &QSlider::setValue );

    connect( contrast, &QSlider::valueChanged, m_contrast, &QSpinBox::setValue );
    connect( threshold, &QSlider::valueChanged, m_threshold, &QSpinBox::setValue );
    connect( dilatation, &QSlider::valueChanged, m_dilatation, &QSpinBox::setValue );
    connect( erosion, &QSlider::valueChanged, m_erosion, &QSpinBox::setValue );
    connect( diceSize, &QSlider::valueChanged, m_diceSize, &QSpinBox::setValue );
    connect( dotSize, &QSlider::valueChanged, m_dotSize, &QSpinBox::setValue );

    QGridLayout* all = new QGridLayout;
    all->addWidget( new QLabel(tr("Contrast"), this), 0, 0 );
    all->addWidget( m_contrast, 0, 1 );
    all->addWidget( contrast, 0, 2 );
    all->addWidget( new QLabel(tr("Threshold"), this), 1, 0 );
    all->addWidget( m_threshold, 1, 1 );
    all->addWidget( threshold, 1, 2 );
    all->addWidget( m_threasholdType, 1, 3 );
    all->addWidget( new QLabel(tr("Dilatation"), this), 2, 0 );
    all->addWidget( m_dilatation, 2, 1 );
    all->addWidget( dilatation, 2, 2 );
    all->addWidget( m_dilatationFirts, 2, 3 );
    all->addWidget( new QLabel(tr("Erosion"), this), 3, 0 );
    all->addWidget( m_erosion, 3, 1 );
    all->addWidget( erosion, 3, 2 );
    all->addWidget( m_erosionFirst, 3, 3 );
    all->addWidget( new QLabel(tr("Dice size"), this), 4, 0 );
    all->addWidget( m_diceSize, 4, 1 );
    all->addWidget( diceSize, 4, 2 );
    all->addWidget( new QLabel(tr("Dot size"), this), 5, 0 );
    all->addWidget( m_dotSize, 5, 1 );
    all->addWidget( dotSize, 5, 2 );

    setLayout( all );
}

void Properties::setContrast(const int c)
{
    if ( m_contrast->value() != c )
        m_contrast->setValue( c );
}

void Properties::setThreshold(const int t)
{
    if ( m_threshold->value() != t )
        m_threshold->setValue( t );
}

void Properties::setDilatation(const int d)
{
    if ( m_dilatation->value() != d )
        m_dilatation->setValue( d );
}

void Properties::setErosion(const int e)
{
    if ( m_erosion->value() != e )
        m_erosion->setValue( e );
}

void Properties::setDiceSize(const int d)
{
    if ( m_diceSize->value() != d )
        m_diceSize->setValue( d );
}

void Properties::setDotSize(const int d)
{
    if ( m_dotSize->value() != d )
        m_dotSize->setValue( d );
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

int Properties::diceSize() const
{
    return m_diceSize->value();
}

int Properties::dotSize() const
{
    return m_dotSize->value();
}

int Properties::thresholdType() const
{
    return m_threasholdType->currentIndex();
}

bool Properties::dilatationFirst() const
{
    return m_dilatationFirts->isChecked();
}
