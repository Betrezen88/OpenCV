#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class CVImageWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openImage();

private:
    void createMenus();

private:
    CVImageWidget* m_cvWidget;
};

#endif // MAINWINDOW_H
