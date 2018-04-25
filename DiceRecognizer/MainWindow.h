#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>

#include "ImageWidget.h"
#include "Player.h"
#include "PlayerControls.h"

class QAction;
class QMenu;
class QTabWidget;
class QThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    bool openFile();
    void play();

private:
    void createActions();
    void createMenu();
    void setConnections(QThread* thread, Player* worker);

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

    QThread* m_thread { 0 };
    Player* m_worker { 0 };
};

#endif // MAINWINDOW_H
