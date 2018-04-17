#ifndef PLAYERCONTROLS_H
#define PLAYERCONTROLS_H

#include <QWidget>

class QPushButton;
class QCheckBox;
class QSlider;
class QLabel;

class PlayerControls : public QWidget
{
    Q_OBJECT
public:
    PlayerControls(QWidget* parent);

signals:
    void play();
    void stop();
    void pause();
    void previous();
    void next();
    void loop(bool l);

public slots:
    void setTotalTime(int t);
    void setCurrentTime(int t);

private:
    QPushButton* m_stop;
    QPushButton* m_pause;
    QPushButton* m_play;
    QPushButton* m_previous;
    QPushButton* m_next;
    QCheckBox* m_loop;
    QSlider* m_time;
    QLabel* m_timeLabel;
};

#endif // PLAYERCONTROLS_H
