#include "Recognizer.h"

Recognizer::Recognizer(PropertiesDialog &propDial)
    : m_propsDial(propDial)
{

}

void Recognizer::recognize(const cv::Mat image)
{
    cv::Rect rect;
    for(int y = m_propsDial.diceSize(); y < image.rows; ++y)
        for(int x = m_propsDial.diceSize(); x < image.cols; ++x)
            if (image.at<uchar>(y, x) == 255)
                recognizeDices(x, y, rect, image);
            else if (image.at<uchar>(y, x) == 0)
                recognizeDots(x, y, rect, image);
}

void Recognizer::drawFoundDices(cv::Mat &image)
{
    int dots = 0;
    for (Dice& dice : m_dices)
    {
//        if (dice.dots().isEmpty())
//            continue;
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
    if (rect.width > m_propsDial.diceSize() && rect.height > m_propsDial.diceSize() )
    {
        Dice dice(rect);
        m_dices.append( dice );
    }
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
    if (rect.width < m_propsDial.diceSize() && rect.height < m_propsDial.diceSize()
        && rect.width > m_propsDial.dotSize() && rect.height > m_propsDial.dotSize())
    {
        cv::Point dot(rect.x + rect.width / 2, rect.y + rect.height / 2);
        for (Dice& dice : m_dices)
            if (dice.boundingBox().contains(dot))
            {
                dice.dots().append(dot);
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
