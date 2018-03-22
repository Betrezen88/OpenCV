#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <QObject>
#include <QDialog>
#include <QSpinBox>

class PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    PropertiesDialog(QWidget *parent = nullptr);
    ~PropertiesDialog();

    int constrast() const { return m_contrast->value(); }
    int threshold() const { return m_threshold->value(); }
    int dilation() const { return m_dilation->value(); }
    int erosion() const { return m_erosion->value(); }

    void setContrast(const int c);
    void setThreshold(const int t);
    void setDilation(const int d);
    void setErosion(const int e);

signals:
    void propertyChanged();

private slots:
    void valueChanged();

private:
    QSpinBox* m_contrast;
    QSpinBox* m_threshold;
    QSpinBox* m_dilation;
    QSpinBox* m_erosion;
};

#endif // PROPERTIESDIALOG_H
