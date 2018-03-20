#ifndef CVIMAGEWIDGET_H
#define CVIMAGEWIDGET_H

#include <QWidget>

#include "opencv2/opencv.hpp"

class QImage;

class CVImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CVImageWidget(QWidget *parent = 0);

//    int width() { return m_image.width(); }
//    int height() { return m_image.height(); }

signals:

public slots:
    void showImage(const cv::Mat& image);

protected:
    void paintEvent(QPaintEvent*);

private:
    QImage m_image;
    cv::Mat m_cvImage;
};

#endif // CVIMAGEWIDGET_H
