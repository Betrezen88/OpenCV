#include "Recognizer.h"

Recognizer::Recognizer(const Properties* properties)
    : m_properties(properties)
{

}

void Recognizer::recognize(const cv::Mat image)
{
    for( int y = m_properties->diceSize(); y < image.rows; ++y )
        for( int x = m_properties->diceSize(); x < image.cols; ++x )
            if ( image.at<uchar>(y, x) == diceColor() )
                recognizeDices(x, y, m_rect, image);
            else if ( image.at<uchar>(y, x) == dotColor() )
                recognizeDots(x, y, m_rect, image);
}

void Recognizer::drawFoundDices(cv::Mat &image)
{
    int dots = 0;

    for(Dice& dice : m_dices)
    {
        if (dice.dots().isEmpty())
            continue;
        dots += dice.dots().size();
        dice.draw(image);
    }

    cv::putText(image,
                "Dice count: " + QString::number(m_dices.size()).toStdString(),
                cv::Point(5, 25),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(0.0, 255.0, 0.0),
                2);
    cv::putText(image,
                "Total score: " + QString::number(dots).toStdString(),
                cv::Point(5, 50),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(0.0, 255.0, 0.0),
                2);
}

void Recognizer::recognizeDices(int x, int y, cv::Rect& rect, const cv::Mat &image)
{
    cv::floodFill(image,
                  cv::Point(x, y),
                  cv::Scalar::all(160),
                  &rect,
                  cv::Scalar::all(0.0),
                  cv::Scalar::all(0.0),
                  CV_FLOODFILL_FIXED_RANGE);
    if ( rect.width > m_properties->diceSize() && rect.height > m_properties->diceSize() )
        m_dices.append( Dice(rect) );
    else
        cv::floodFill(image,
                      cv::Point(x, y),
                      cv::Scalar::all(32),
                      &rect,
                      cv::Scalar::all(0.0),
                      cv::Scalar::all(0.0),
                      CV_FLOODFILL_FIXED_RANGE);
}

void Recognizer::recognizeDots(int x, int y, cv::Rect &rect, const cv::Mat &image)
{
    cv::floodFill(image,
                  cv::Point(x, y),
                  cv::Scalar::all(96),
                  &rect,
                  cv::Scalar::all(0.0),
                  cv::Scalar::all(0.0),
                  CV_FLOODFILL_FIXED_RANGE);

    if ( (rect.width < m_properties->diceSize()) && (rect.height < m_properties->diceSize())
         && (rect.width > m_properties->dotSize()) && (rect.height > m_properties->dotSize()) )
    {
        cv::Point dot(rect.x + rect.width / 2, rect.y + rect.height / 2);
        for (Dice& dice : m_dices)
            if (dice.boundingBox().contains(dot))
            {
                dice.addDot( dot );
                break;
            }
    }
    else
    {
        cv::floodFill(image,
                      cv::Point(x,y),
                      cv::Scalar::all(32),
                      &rect,
                      cv::Scalar::all(0.0),
                      cv::Scalar::all(0.0),
                      CV_FLOODFILL_FIXED_RANGE);
    }
}

int Recognizer::diceColor() const
{
    if ( (m_properties->thresholdType() == 1) || (m_properties->thresholdType() == 4) )
        return 0;
    return 255;
}

int Recognizer::dotColor() const
{
    if ( (m_properties->thresholdType() == 1) || (m_properties->thresholdType() == 4) )
        return 255;
    return 0;
}
