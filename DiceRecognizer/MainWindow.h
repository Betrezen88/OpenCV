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

public slots:
    bool openFile();

private:
    void createActions();
    void createMenu();

private:
    QMenu* m_fileMenu;

    QAction* m_openFileAct;
    QAction* m_quitAct;
};

#endif // MAINWINDOW_H
