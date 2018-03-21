#include "ContrastEnhancement.h"

ContrastEnhancement::ContrastEnhancement(cv::Mat image, double alpha) : m_image(image)
{
    uchar* ptrImg = m_image.data;
    int size = m_image.rows * m_image.cols;
    double intensity;
    for (int i=0; i<size; ++i)
    {
        intensity = alpha * (static_cast<double>(ptrImg[i]) / 255.0 - 0.5) + 0.5;

        if (intensity < 0.0)
            ptrImg[i] = 0;
        else if (intensity < 1.0)
            ptrImg[i] = intensity * 255;
        else
            ptrImg[i] = 255;
    }

}
