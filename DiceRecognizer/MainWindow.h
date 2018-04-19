#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "ImageProcessor.h"
#include "ImageWigdet.h"
#include "Properties.h"
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

private slots:
    bool openFile();
    void showProperties();
    void displayError(const QString message);
    void updateImages(const QVector<cv::Mat> images);
    void play();

private:
    void createMenu();
    void createActions();

private:
    QMenu* m_fileMenu;
    QAction* m_openFileAct;
    QAction* m_showPropertiesAct;

    QTabWidget* m_tabWidget;

    ImageWidget* m_input;
    ImageWidget* m_gray;
    ImageWidget* m_threshold;
    ImageWidget* m_filter;
    ImageWidget* m_output;

    Properties* m_properties;
    Player* m_player;
    PlayerControls* m_playerControlls;
};

#endif // MAINWINDOW_H
