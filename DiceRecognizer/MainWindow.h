#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QThread>

#include "ImageWidget.h"
#include "Player.h"
#include "PlayerControls.h"
#include "Properties.h"

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
    void openFile();
    void openProperties();

private slots:
    void clean();
    void updateImages(const cv::Mat img);

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

    Properties* m_properties;

    QMenu* m_fileMenu;

    QAction* m_openFileAct;
    QAction* m_openPropertiesAct;
    QAction* m_quitAct;

    QString m_filePath;

    QScopedPointer<Player> m_player { nullptr };
    QScopedPointer<QThread> m_thread { nullptr };
};

#endif // MAINWINDOW_H
