#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <QDialog>
#include <QObject>

class QSpinBox;
class QComboBox;
class QRadioButton;

class Properties : public QDialog
{
    Q_OBJECT
public:
    Properties(QWidget *parent = 0);

    void setContrast(const int c);
    void setThreshold(const int t);
    void setDilatation(const int d);
    void setErosion(const int e);
    void setDiceSize(const int d);
    void setDotSize(const int d);

    int contrast() const;
    int threshold() const;
    int dilatation() const;
    int erosion() const;
    int diceSize() const;
    int dotSize() const;
    int thresholdType() const;
    bool dilatationFirst() const;

private:
    QSpinBox* m_contrast;
    QSpinBox* m_threshold;
    QSpinBox* m_dilatation;
    QSpinBox* m_erosion;
    QSpinBox* m_diceSize;
    QSpinBox* m_dotSize;
    QComboBox* m_threasholdType;
    QRadioButton* m_dilatationFirts;
    QRadioButton* m_erosionFirst;

    QStringList m_types;
};

#endif // PROPERTIES_H
