#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QDialog>
#include <QObject>

class QSpinBox;

class Properties : public QDialog
{
    Q_OBJECT
public:
    Properties(QWidget *parent = 0);

    void setContrast(const int c);
    void setThreshold(const int t);
    void setDilatation(const int d);
    void setErosion(const int e);

    int contrast() const;
    int threshold() const;
    int dilatation() const;
    int erosion() const;

signals:
    void valueChanged();

private:
    QSpinBox* m_contrast;
    QSpinBox* m_threshold;
    QSpinBox* m_dilatation;
    QSpinBox* m_erosion;
};

#endif // PROPERTIES_H
