#include "ImageProcessor.h"
#include "Recognizer.h"

ImageProcessor::ImageProcessor(const Properties* properties)
    : m_properties(properties)
{

}

ImageProcessor::~ImageProcessor()
{

}

const QHash<QString, cv::Mat> ImageProcessor::processImage(const cv::Mat& img)
{
    cv::Mat input = img;
    cv::Mat gray;
    cv::Mat threshold;
    cv::Mat filter;
    cv::Mat output;

    cv::cvtColor( input, gray, CV_BGR2GRAY );
    enhance( gray, static_cast<double>(m_properties->contrast()) / 50.0 );
    cv::threshold( gray, threshold, m_properties->threshold(), 255, m_properties->thresholdType() );

    threshold.copyTo(filter);

    if ( m_properties->dilatationFirst() )
    {
        if ( m_properties->dilatation() )
            cv::dilate( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->dilatation() );
        if ( m_properties->erosion() )
            cv::erode( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->erosion() );
    }
    else
    {
        if ( m_properties->erosion() )
            cv::erode( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->erosion() );
        if ( m_properties->dilatation() )
            cv::dilate( filter, filter, cv::Mat(), cv::Point(-1, -1), m_properties->dilatation() );
    }

    input.copyTo( output );

    Recognizer recog( m_properties );
    recog.recognize( filter );
    recog.drawFoundDices( output );

    QHash<QString, cv::Mat> result;
    result.insert( "input", input );
    result.insert( "gray", gray );
    result.insert( "threshold", threshold );
    result.insert( "filter", filter );
    result.insert( "output", output );

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
