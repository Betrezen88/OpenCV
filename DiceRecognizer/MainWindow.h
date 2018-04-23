#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ImageWidget.h"
#include "PlayerControls.h"

class QAction;
class QMenu;
class QTabWidget;

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
    QTabWidget* m_tabs;

    ImageWidget* m_input;
    ImageWidget* m_gray;
    ImageWidget* m_threshold;
    ImageWidget* m_filter;
    ImageWidget* m_output;

    PlayerControls* m_playerControls;

    QMenu* m_fileMenu;

    QAction* m_openFileAct;
    QAction* m_quitAct;

    QString m_filePath;
};

#endif // MAINWINDOW_H
