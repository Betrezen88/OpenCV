#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QHash>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

#include "ImageProcessor.h"
#include "Properties.h"

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(const Properties* properties, QObject *parent = 0);
    ~Player();

    void setFilePath(const QString& filePath);
    const QString filePath() const;

signals:
    void newFrameCount(const int frameCount);
    void newCurrentFrameNumber(const int frameNumber);
    void resultReady(const QHash<QString, cv::Mat>);
    void newSize(const int width, const int height);
    void singleImage(const bool s);
    void filePathChanged();
    void finished();

public slots:
    void process();
    void stop();
    void play();
    void pause();
    void next();
    void previous();
    void loop(const bool l);

private slots:
    void openFile();

private:
    void processImage(const cv::Mat& img);
    bool readNonEmptyFrame();
    void resetDisplay();

private:
    enum class State { IDLE, STOP, PAUSE, PLAY, NEXT, PREVIOUS, END };

    const Properties* m_properties;
    ImageProcessor* m_imgProc;
    bool m_loop;
    State m_state;

    QString m_filePath;

    cv::VideoCapture m_capture;
    cv::Mat m_frame;

    int m_delay { 0 };
};

#endif // PLAYER_H
