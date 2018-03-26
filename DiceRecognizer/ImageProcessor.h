#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "PropertiesDialog.h"

#include <QObject>

class ImageProcessor : public QObject
{
    Q_OBJECT
public:
    ImageProcessor(PropertiesDialog& propsDial);
    ~ImageProcessor() = default;

    cv::Mat inputImage() { return m_inputImage; }
    cv::Mat grayImage() { return m_grayImage; }
    cv::Mat thresholdedImage() { return m_thresholdedImage; }
    cv::Mat filteredImage() { return m_filtratedImage; }
    cv::Mat outputImage() { return m_outputImage; }

    void process(const cv::Mat image);
    void process(cv::VideoCapture video);

signals:
    void finished();

private slots:
    void reprocess();

private:
    void grayscale(cv::Mat& image);
    void enhance(cv::Mat& image);
    void segmentation(cv::Mat& image);
    void threshold(cv::Mat& image);
    void filter(cv::Mat& image);

private:
    cv::Mat m_inputImage;
    cv::Mat m_grayImage;
    cv::Mat m_thresholdedImage;
    cv::Mat m_filtratedImage;
    cv::Mat m_outputImage;
    PropertiesDialog& m_propsDial;
};

#endif // IMAGEPROCESSOR_H
