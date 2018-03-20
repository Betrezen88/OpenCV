#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class CVImageWidget;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void showContextMenu(const QPoint&);
    void loadImage();

private:
    CVImageWidget* m_cvWidget;
};

#endif // DIALOG_H
