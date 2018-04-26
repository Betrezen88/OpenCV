#ifndef DICE_H
#define DICE_H

#include <opencv2/opencv.hpp>

#include <QVector>

class Dice
{
public:
    Dice();
    Dice(cv::Rect rect);
    ~Dice();

    void draw(cv::Mat &image);
    void addDot(const cv::Point dot);
    const cv::Rect& boundingBox() const { return m_boundingBox; }
    const QVector<cv::Point>& dots() const { return m_dots; }

private:
    cv::Rect m_boundingBox;
    QVector<cv::Point> m_dots;
    cv::Scalar m_color;
};

#endif // DICE_H
