#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTabWidget;

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
    QTabWidget* m_tabWidget;
};

#endif // MAINWINDOW_H
