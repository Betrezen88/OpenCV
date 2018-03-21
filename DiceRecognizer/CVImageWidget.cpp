#include "CVImageWidget.h"

#include <QPainter>

CVImageWidget::CVImageWidget(QWidget *parent) : QWidget(parent)
{

}

void CVImageWidget::showImage(const cv::Mat &image)
{
    cv::Mat tmpCV;
    switch(image.type())
    {
        case CV_8UC1:
            cvtColor(image, tmpCV, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cvtColor(image, tmpCV, CV_BGR2RGB);
            break;
    }

    if (tmpCV.isContinuous())
    {
        m_image = QImage(tmpCV.data, tmpCV.cols, tmpCV.rows, tmpCV.cols*3, QImage::Format_RGB888);
        this->setFixedSize(image.cols, image.rows);
        repaint();
    }
}

void CVImageWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), m_image);
}
