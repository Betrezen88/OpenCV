#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>

#include <QVector>

#include "Properties.h"
#include "Dice.h"

class Recognizer
{
public:
    Recognizer(const Properties* properties);

    void recognize(const cv::Mat image);
    void drawFoundDices(cv::Mat& image);

private:
    void recognizeDices(int x, int y, cv::Rect& rect, const cv::Mat& image);
    void recognizeDots(int x, int y, cv::Rect& rect, const cv::Mat &image);
    int diceColor() const;
    int dotColor() const;

private:
    const Properties* m_properties;
    QVector<Dice> m_dices;
    cv::Rect m_rect;
};

#endif // RECOGNIZER_H
