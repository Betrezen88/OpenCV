#include "ImageProcessor.h"
#include "ContrastEnhancement.h"
#include "Recognizer.h"

#include <QMessageBox>

ImageProcessor::ImageProcessor(PropertiesDialog &propsDial)
    : m_propsDial(propsDial)
{
    connect(&m_propsDial, &PropertiesDialog::propertyChanged, this, &ImageProcessor::reprocess);
}

void ImageProcessor::process(const cv::Mat image)
{
    if (!image.empty())
    {
        image.copyTo(m_inputImage);
        // Process steps
        // 1) Convert to grayscale
        grayscale(m_inputImage);
        // 2) Enhance grayscaled
        enhance(m_grayImage);
        // 3) Segmentation
        segmentation(m_grayImage);
    }
    emit finished();
}

void ImageProcessor::reprocess()
{
    if (!m_inputImage.empty())
        process(m_inputImage);
}

void ImageProcessor::grayscale(cv::Mat& image)
{
    if (image.empty())
    {
        QMessageBox::warning(0, tr("Empty image"), tr("Empty image"), QMessageBox::Ok, QMessageBox::Cancel);
        return;
    }
    cv::cvtColor(image, m_grayImage, CV_BGR2GRAY);
}

void ImageProcessor::enhance(cv::Mat &image)
{
    m_grayImage = ContrastEnhancement(image, m_propsDial.constrast() / 50.0).image();
}

void ImageProcessor::segmentation(cv::Mat& image)
{
    // Segmentation steps
    // 1) Threshold image
    threshold(image);
    // 2) Filtrate image
    filter(m_thresholdedImage);
    Recognizer recog;
    recog.recognize(m_filtratedImage);
    m_inputImage.copyTo(m_outputImage);
    recog.drawFoundDices(m_outputImage);
}

void ImageProcessor::threshold(cv::Mat &image)
{
    cv::threshold(image, m_thresholdedImage, m_propsDial.threshold(), 255, CV_THRESH_BINARY);
}

void ImageProcessor::filter(cv::Mat &image)
{
    if (m_propsDial.dilation())
        cv::dilate(image, m_filtratedImage, cv::Mat(), cv::Point(-1, -1), m_propsDial.dilation());
    else
        image.copyTo(m_filtratedImage);

    if (m_propsDial.erosion())
        cv::erode(m_filtratedImage, m_filtratedImage, cv::Mat(), cv::Point(-1, -1), m_propsDial.erosion());
}
