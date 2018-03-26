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
    int diceSize() const { return m_diceSize->value(); }
    int dotSize() const { return m_dotSize->value(); }

    void setContrast(const int c);
    void setThreshold(const int t);
    void setDilation(const int d);
    void setErosion(const int e);
    void setDiceSize(const int d);
    void setDotSize(const int d);

signals:
    void propertyChanged();

private slots:
    void valueChanged();

private:
    QSpinBox* m_contrast;
    QSpinBox* m_threshold;
    QSpinBox* m_dilation;
    QSpinBox* m_erosion;
    QSpinBox* m_diceSize;
    QSpinBox* m_dotSize;
};

#endif // PROPERTIESDIALOG_H
