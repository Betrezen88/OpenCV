#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScopedPointer>
#include <QThread>

#include "ImageWidget.h"
#include "Player.h"
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
    void openFile();

private slots:
    void clean();

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

    QScopedPointer<Player> m_player { nullptr };
    QScopedPointer<QThread> m_thread { nullptr };

    bool m_exists;
};

#endif // MAINWINDOW_H
