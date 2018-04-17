#include "Dice.h"

Dice::Dice()
{

}

Dice::Dice(cv::Rect rect) : m_boundingBox(rect)
{
    m_color = cv::Scalar(0, 255, 0);
}

Dice::~Dice()
{

}

void Dice::draw(cv::Mat& image)
{
//    if (m_dots.isEmpty())
//        return;

    cv::rectangle(image, m_boundingBox, m_color, 2);

    for (const cv::Point& dot : m_dots)
        cv::circle(image, dot, (m_boundingBox.width + m_boundingBox.height) / 16, m_color, -1);

    cv::putText(image,
                QString::number(m_dots.size()).toStdString(),
                cv::Point(m_boundingBox.x, m_boundingBox.y -3),
                cv::FONT_HERSHEY_SIMPLEX,
                1.0,
                cv::Scalar(0.0, 255.0, 0.0),
                2);
}
