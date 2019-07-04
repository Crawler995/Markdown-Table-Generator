#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPoint>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QObject>
#include <QEvent>
#include <QPaintEvent>

#include "titlebar.h"

#define DRAG_WIDTH 3

enum Direction {RIGHT, RIGHT_BOTTOM, BOTTOM, OTHERS};

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    TitleBar *titleBar;
    QWidget *contentWidget;
    QVBoxLayout *layout;

    bool isMouseLeftBtnPressDown;
    QPoint dragPoint;
    Direction dragDir;

    void setWindowSize();
    void setWindowStyle();
    void initWindowComponent(QWidget *contentWidget);

    void dragDirectionHandle(const QPoint &cursorGlobalPoint);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
