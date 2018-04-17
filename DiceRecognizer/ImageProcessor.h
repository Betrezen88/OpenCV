#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QVector>
#include <QImage>

#include <opencv2/opencv.hpp>

#include "Properties.h"

class ImageProcessor : public QObject
{
    Q_OBJECT
public:
    ImageProcessor(const Properties* properties);
    ~ImageProcessor();

signals:
    void resultReady(const QVector<cv::Mat> images);

public slots:
    QVector<cv::Mat> processImage(const cv::Mat &img);

private:
    void enhance(cv::Mat img, double alpha);

private:
    const Properties* m_properties;
};

#endif // IMAGEPROCESSOR_H
