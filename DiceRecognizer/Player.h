#ifndef PLAYER_H
#define PLAYER_H

#include <QThread>
#include <QObject>
#include <QVector>

#include "Properties.h"
#include "ImageProcessor.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

class Player : public QThread
{
    Q_OBJECT
public:
    explicit Player(const Properties* properties);

    void setFilePath(const QString& filePath);
    QString filePath() const;

    bool isStopped();
    bool isPaused();

signals:
    void totalFrameCount(int frames);
    void currentFrameNumber(int f);
    void resultReady(QVector<cv::Mat> result);

public slots:
    void play();
    void pause();
    void stop();
    void setLoop(bool l);

protected:
    void run();

private:
    const Properties* m_properties;

    QString m_filePath;
    bool m_stop;
    bool m_pause;
    bool m_loop;
    int m_totalFrameCount;

    cv::VideoCapture capture;
};

#endif // PLAYER_H
