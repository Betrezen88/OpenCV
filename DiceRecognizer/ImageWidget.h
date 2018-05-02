#ifndef IMAGEWIGDET_H
#define IMAGEWIGDET_H

#include <QWidget>
#include <QImage>

#include <opencv2/opencv.hpp>

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

public slots:
    void showImage(const cv::Mat& image);

protected:
    void paintEvent(QPaintEvent*);

private:
    QImage m_image;
    cv::Mat m_cvImage;
};

#endif // IMAGEWIGDET_H
