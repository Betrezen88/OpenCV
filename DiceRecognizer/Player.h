#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

    void setFilePath(const QString& filePath);
    const QString filePath() const;

signals:
    void resultReady(const cv::Mat img);
    void finished();

public slots:
    void process();
    void stop();
    void play();
    void pause();
    void next();
    void previous();
    void loop(const bool l);

private:
    QString m_filePath;
    bool m_stop;
    bool m_pause;
    bool m_loop;

    cv::VideoCapture m_capture;
    cv::Mat m_frame;

    int m_delay;
};

#endif // PLAYER_H
