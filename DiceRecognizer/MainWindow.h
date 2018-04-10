#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openImage();

private:
    void createMenu();
    void createActions();

private:
    QMenu* m_fileMenu;
    QAction* m_openImageAct;
};

#endif // MAINWINDOW_H
