#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>
#include <QHash>
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
    void resultReady(const QHash<QString, cv::Mat> images);

public slots:
    const QHash<QString, cv::Mat> processImage(const cv::Mat img);

private:
    void enhance(cv::Mat img, double alpha);

private:
    const Properties* m_properties;
};

#endif // IMAGEPROCESSOR_H
