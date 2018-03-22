#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QObject>
#include <QDialog>
#include <QSpinBox>

class PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    PropertiesDialog();
    ~PropertiesDialog();

    int constrast() const { return m_contrast->value(); }
    int threshold() const { return m_threshold->value(); }
    int dilation() const { return m_dilation->value(); }
    int erosion() const { return m_erosion->value(); }

    void setContrast(const int c) { m_contrast->setValue(c); }
    void setThreshold(const int t) { m_threshold->setValue(t); }
    void setDilation(const int d) { m_dilation->setValue(d); }
    void setErosion(const int e) { m_erosion->setValue(e); }

private:
    QSpinBox* m_contrast;
    QSpinBox* m_threshold;
    QSpinBox* m_dilation;
    QSpinBox* m_erosion;
};

#endif // PROPERTIESDIALOG_H
