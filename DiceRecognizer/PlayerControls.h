#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QWidget>

class QCheckBox;
class QLabel;
class QPushButton;
class QSlider;

class PlayerControls : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerControls(QWidget *parent = 0);

signals:
    void stop();
    void play();
    void pause();
    void previous();
    void next();
    void loop(const bool l);

public slots:
    void updateFrameCount(const int frameCount);

private:
    QPushButton* m_stopBtn;
    QPushButton* m_playBtn;
    QPushButton* m_pauseBtn;
    QPushButton* m_previousBtn;
    QPushButton* m_nextBtn;
    QCheckBox* m_loop;
    QSlider* m_time;
    QLabel* m_timeL;
};

#endif // PLAYERCONTROLS_H
