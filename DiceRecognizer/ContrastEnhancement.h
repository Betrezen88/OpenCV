#ifndef CONTRASTENHANCEMENT_H
#define CONTRASTENHANCEMENT_H

#include <opencv2/opencv.hpp>

class ContrastEnhancement
{
public:
    ContrastEnhancement(cv::Mat image, double alpha);

    cv::Mat image() { return m_image; }

private:
    cv::Mat m_image;
};

#endif // CONTRASTENHANCEMENT_H
