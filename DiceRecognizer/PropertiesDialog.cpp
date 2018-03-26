#include "PropertiesDialog.h"

#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QSlider>
#include <QtGlobal>

PropertiesDialog::PropertiesDialog(QWidget *parent)
    : QDialog(parent)
{
    m_contrast = new QSpinBox(this);
    m_threshold = new QSpinBox(this);
    m_dilation = new QSpinBox(this);
    m_erosion = new QSpinBox(this);
    m_diceSize = new QSpinBox(this);
    m_dotSize = new QSpinBox(this);

    m_contrast->setRange(0, 100);
    m_threshold->setRange(0, 255);
    m_dilation->setRange(0, 50);
    m_erosion->setRange(0, 50);
    m_diceSize->setRange(0, 100);
    m_dotSize->setRange(0, 100);

    QSlider* contrast = new QSlider(Qt::Horizontal ,this);
    QSlider* threshol = new QSlider(Qt::Horizontal ,this);
    QSlider* dilation = new QSlider(Qt::Horizontal ,this);
    QSlider* erosion = new QSlider(Qt::Horizontal ,this);
    QSlider* diceSize = new QSlider(Qt::Horizontal ,this);
    QSlider* dotSize = new QSlider(Qt::Horizontal ,this);

    threshol->setRange(0, 255);

    connect(contrast, &QSlider::valueChanged, m_contrast, &QSpinBox::setValue);
    connect(m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), contrast, &QSlider::setValue);

    connect(threshol, &QSlider::valueChanged, m_threshold, &QSpinBox::setValue);
    connect(m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), threshol, &QSlider::setValue);

    connect(dilation, &QSlider::valueChanged, m_dilation, &QSpinBox::setValue);
    connect(m_dilation, QOverload<int>::of(&QSpinBox::valueChanged), dilation, &QSlider::setValue);

    connect(erosion, &QSlider::valueChanged, m_erosion, &QSpinBox::setValue);
    connect(m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), erosion, &QSlider::setValue);

    connect(diceSize, &QSlider::valueChanged, m_diceSize, &QSpinBox::setValue);
    connect(m_diceSize, QOverload<int>::of(&QSpinBox::valueChanged), diceSize, &QSlider::setValue);

    connect(dotSize, &QSlider::valueChanged, m_dotSize, &QSpinBox::setValue);
    connect(m_dotSize, QOverload<int>::of(&QSpinBox::valueChanged), dotSize, &QSlider::setValue);

    connect(m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);
    connect(m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);
    connect(m_dilation, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);
    connect(m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);
    connect(m_diceSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);
    connect(m_dotSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &PropertiesDialog::valueChanged);

    QGridLayout* all = new QGridLayout;
    all->addWidget(new QLabel(tr("Contrast:")), 0, 0);
    all->addWidget(m_contrast, 0, 1);
    all->addWidget(contrast, 0, 2);
    all->addWidget(new QLabel(tr("Threshold:")), 1, 0);
    all->addWidget(m_threshold, 1, 1);
    all->addWidget(threshol, 1, 2);
    all->addWidget(new QLabel(tr("Dilation:")), 2, 0);
    all->addWidget(m_dilation, 2, 1);
    all->addWidget(dilation, 2, 2);
    all->addWidget(new QLabel(tr("Erosion:")), 3, 0);
    all->addWidget(m_erosion, 3, 1);
    all->addWidget(erosion, 3, 2);
    all->addWidget(new QLabel(tr("Dice size:")), 4, 0);
    all->addWidget(m_diceSize, 4, 1);
    all->addWidget(diceSize, 4, 2);
    all->addWidget(new QLabel(tr("Dot size:")), 5, 0);
    all->addWidget(m_dotSize, 5, 1);
    all->addWidget(dotSize, 5, 2);

    setLayout(all);
}

PropertiesDialog::~PropertiesDialog()
{

}

void PropertiesDialog::setContrast(const int c)
{
    m_contrast->setValue(c);
    emit propertyChanged();
}

void PropertiesDialog::setThreshold(const int t)
{
    m_threshold->setValue(t);
    emit propertyChanged();
}

void PropertiesDialog::setDilation(const int d)
{
    m_dilation->setValue(d);
    emit propertyChanged();
}

void PropertiesDialog::setErosion(const int e)
{
    m_erosion->setValue(e);
    emit propertyChanged();
}

void PropertiesDialog::setDiceSize(const int d)
{
    m_diceSize->setValue(d);
    emit propertyChanged();
}

void PropertiesDialog::setDotSize(const int d)
{
    m_dotSize->setValue(d);
    emit propertyChanged();
}

void PropertiesDialog::valueChanged()
{
    emit propertyChanged();
}
