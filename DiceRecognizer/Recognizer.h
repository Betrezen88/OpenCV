#ifndef RECOGNIZER_H
#define RECOGNIZER_H

#include <opencv2/opencv.hpp>

#include <QVector>

#include "Dice.h"

class Recognizer
{
public:
    Recognizer();

    void recognize(const cv::Mat image);
    void drawFoundDices(cv::Mat& image);

private:
    void recognizeDices(int x, int y, cv::Rect& rect, const cv::Mat& image);
    void recognizeDots(int x, int y, cv::Rect& rect, const cv::Mat &image);

private:
    QVector<Dice> m_dices;
};

#endif // RECOGNIZER_H
