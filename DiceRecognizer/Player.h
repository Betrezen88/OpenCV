#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include <opencv2/opencv.hpp>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

    void setFilePath(const QString& filePath);
    const QString filePath() const;

    bool isWorking() const;

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
    bool m_working;
    bool m_stop;
    bool m_pause;
    bool m_loop;
};

#endif // PLAYER_H
