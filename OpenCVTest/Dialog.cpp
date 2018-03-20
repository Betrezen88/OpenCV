#include "Dialog.h"
#include "CVImageWidget.h"

#include <QFileDialog>
#include <QMenu>
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumSize(200, 200);
    setContextMenuPolicy(Qt::CustomContextMenu);

    connect(this, &Dialog::customContextMenuRequested, this, &Dialog::showContextMenu);

    m_cvWidget = new CVImageWidget(this);

//    cv::Mat inputImage = cv::imread("/home/miwy/Pictures/img_fjords.jpg");

//    m_cvWidget->showImage(inputImage);

    QVBoxLayout* all = new QVBoxLayout(this);
    all->addWidget(m_cvWidget);
}

Dialog::~Dialog()
{

}

void Dialog::showContextMenu(const QPoint & pos)
{
    QMenu contextMenu(tr("Context Menu"));

    QAction loadImageAct("Load Image", this);

    contextMenu.addAction(&loadImageAct);
    connect(&loadImageAct, &QAction::triggered, this, &Dialog::loadImage);

    contextMenu.exec(mapToGlobal(pos));
}

void Dialog::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.jpeg, *.png, *.jpg)"));

    cv::Mat cvImage = cv::imread(fileName.toStdString());

    m_cvWidget->showImage(cvImage);

    resize(m_cvWidget->width()+20, m_cvWidget->height()+20);
}
