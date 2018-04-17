#include "ImageProcessor.h"
#include "Recognizer.h"

#include <QDebug>

ImageProcessor::ImageProcessor(const Properties* properties)
    : m_properties(properties)
{

}

ImageProcessor::~ImageProcessor()
{

}

QVector<cv::Mat> ImageProcessor::processImage(const cv::Mat& img)
{
    cv::Mat input = img;
    cv::Mat gray;
    cv::Mat threshold;
    cv::Mat filter;
    cv::Mat output;

    cv::cvtColor( input, gray, CV_BGR2GRAY );
    enhance( gray, static_cast<double>(m_properties->contrast()) / 50.0 );
    cv::threshold( gray, threshold, m_properties->threshold(), 255, CV_THRESH_BINARY );

    threshold.copyTo(filter);

    if ( m_properties->dilatation() )
        cv::dilate( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->dilatation() );
    if ( m_properties->erosion() )
        cv::erode( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->erosion() );

    input.copyTo( output );

    Recognizer recog;
    recog.recognize( filter );
    recog.drawFoundDices( output );

    QVector<cv::Mat> result;
    result.append( input );
    result.append( gray );
    result.append( threshold );
    result.append( filter );
    result.append( output );

    return result;
}

void ImageProcessor::enhance(cv::Mat img, double alpha)
{
    uchar* ptrImg = img.data;
    int size = img.rows * img.cols;
    double intensity;
    for (int i=0; i<size; ++i)
    {
        intensity = alpha * (static_cast<double>(ptrImg[i]) / 255.0 - 0.5) + 0.5;

        if (intensity < 0.0)
            ptrImg[i] = 0;
        else if (intensity < 1.0)
            ptrImg[i] = intensity * 255;
        else
            ptrImg[i] = 255;
    }
}
