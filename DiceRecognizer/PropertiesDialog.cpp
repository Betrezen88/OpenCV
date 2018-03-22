#include "PropertiesDialog.h"

#include <QLabel>
#include <QSpinBox>
#include <QGridLayout>
#include <QSlider>
#include <QtGlobal>

PropertiesDialog::PropertiesDialog()
{
    m_contrast = new QSpinBox(this);
    m_threshold = new QSpinBox(this);
    m_dilation = new QSpinBox(this);
    m_erosion = new QSpinBox(this);

    m_contrast->setRange(0, 100);
    m_threshold->setRange(0, 255);
    m_dilation->setRange(0, 50);
    m_erosion->setRange(0, 50);

    QSlider* contrast = new QSlider(Qt::Horizontal ,this);
    QSlider* threshol = new QSlider(Qt::Horizontal ,this);
    QSlider* dilation = new QSlider(Qt::Horizontal ,this);
    QSlider* erosion = new QSlider(Qt::Horizontal ,this);

    connect(contrast, &QSlider::valueChanged, m_contrast, &QSpinBox::setValue);
    connect(m_contrast, QOverload<int>::of(&QSpinBox::valueChanged), contrast, &QSlider::setValue);

    connect(threshol, &QSlider::valueChanged, m_threshold, &QSpinBox::setValue);
    connect(m_threshold, QOverload<int>::of(&QSpinBox::valueChanged), threshol, &QSlider::setValue);

    connect(dilation, &QSlider::valueChanged, m_dilation, &QSpinBox::setValue);
    connect(m_dilation, QOverload<int>::of(&QSpinBox::valueChanged), dilation, &QSlider::setValue);

    connect(erosion, &QSlider::valueChanged, m_erosion, &QSpinBox::setValue);
    connect(m_erosion, QOverload<int>::of(&QSpinBox::valueChanged), erosion, &QSlider::setValue);

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

    setLayout(all);
}

PropertiesDialog::~PropertiesDialog()
{

}
