#ifndef PLAYER_H
#define PLAYER_H

#include <QThread>
#include <QObject>
#include <QVector>
#include <QScopedPointer>

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
    void singleImage(bool y);
    void resultReady(QVector<cv::Mat> result);

public slots:
    void play();
    void pause();
    void stop();
    void setLoop(bool l);
    void nextFrame();
    void previousFrame();

protected:
    void run();

private:
    bool readNonEmptyFrame(cv::Mat& frame);
    void processFrame(const cv::Mat& frame);

private:
    const Properties* m_properties;

    QString m_filePath;
    bool m_stop;
    bool m_pause;
    bool m_loop;
    int m_totalFrameCount;

    QScopedPointer<ImageProcessor> m_worker;
    cv::VideoCapture m_capture;
    cv::Mat m_frame;
};

#endif // PLAYER_H
