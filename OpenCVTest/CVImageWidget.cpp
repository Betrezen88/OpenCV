#include <QImage>
#include <QPainter>

#include "CVImageWidget.h"

CVImageWidget::CVImageWidget(QWidget *parent) : QWidget(parent)
{

}

void CVImageWidget::showImage(const cv::Mat &image)
{
    switch(image.type())
    {
        case CV_8UC1:
            cvtColor(image, m_cvImage, CV_GRAY2RGB);
            break;
        case CV_8UC3:
            cvtColor(image, m_cvImage, CV_BGR2RGB);
            break;
    }

    if (m_cvImage.isContinuous())
    {
        m_image = QImage(m_cvImage.data, m_cvImage.cols, m_cvImage.rows, m_cvImage.cols*3, QImage::Format_RGB888);
        this->setFixedSize(image.cols, image.rows);
        repaint();
    }
}

void CVImageWidget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), m_image);
}
