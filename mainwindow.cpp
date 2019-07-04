#include "mainwindow.h"
#include "titlebar.h"
#include "colorboard.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QString>
#include <QMouseEvent>
#include <QRect>
#include <QVBoxLayout>
#include <QDebug>
#include <QObject>
#include <QEvent>
#include <QPalette>
#include <QGraphicsDropShadowEffect>
#include <QPainterPath>
#include <QPainter>
#include <QBrush>
#include <QtMath>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    isMouseLeftBtnPressDown = false;
    dragDir = OTHERS;
    setMouseTracking(true);

    setWindowSize();
    setWindowStyle();
}

void MainWindow::setWindowSize() {
    int screenWidth = QApplication::desktop()->screenGeometry().width();
    int screenHeight = QApplication::desktop()->screenGeometry().height();

    resize(screenWidth / 2, screenHeight / 2);
}

void MainWindow::setWindowStyle() {
    setWindowFlags(Qt::FramelessWindowHint);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    setPalette(palette);
    setAutoFillBackground(true);
}

void MainWindow::initWindowComponent(QWidget *contentWidget) {
    layout = new QVBoxLayout(this);

    titleBar = new TitleBar("Markdown表格生成器", this);

    layout->addWidget(titleBar);
    layout->addWidget(contentWidget);
    layout->setSpacing(0);

    int margin = 5 * DRAG_WIDTH;
    layout->setContentsMargins(margin, 0, margin, margin);

    setLayout(layout);
}

void MainWindow::dragDirectionHandle(const QPoint &cursorGlobalPoint) {
    QRect rect = this->rect();
    QPoint rb = mapToGlobal(rect.bottomRight());

    int x = cursorGlobalPoint.x();
    int y = cursorGlobalPoint.y();

    bool isDragRight = x >= rb.x() - DRAG_WIDTH && x <= rb.x();
    bool isDragBottom = y >= rb.y() - DRAG_WIDTH && y <= rb.y();

    if(isDragRight && isDragBottom) {
        dragDir = RIGHT_BOTTOM;
        setCursor(Qt::SizeFDiagCursor);
    }
    else if(isDragRight) {
        dragDir = RIGHT;
        setCursor(Qt::SizeHorCursor);
    }
    else if(isDragBottom) {
        dragDir = BOTTOM;
        setCursor(Qt::SizeVerCursor);
    }
    else {
        dragDir = OTHERS;
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        isMouseLeftBtnPressDown = false;

        if(dragDir != OTHERS) {
            releaseMouse();
            setCursor(Qt::ArrowCursor);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        isMouseLeftBtnPressDown = true;
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    QPoint gloPoint = event->globalPos();
    QRect rect = this->rect();
    QPoint tl = mapToGlobal(rect.topLeft());
    QPoint rb = mapToGlobal(rect.bottomRight());

    if(!isMouseLeftBtnPressDown) {
        dragDirectionHandle(gloPoint);
    }
    else {
        if(dragDir == OTHERS) {
            return;
        }

        QRect target(tl, rb);
        switch(dragDir) {
        case RIGHT:
            target.setWidth(gloPoint.x() - tl.x());
            break;
        case BOTTOM:
            target.setHeight(gloPoint.y() - tl.y());
            break;
        case RIGHT_BOTTOM:
            target.setWidth(gloPoint.x() - tl.x());
            target.setHeight(gloPoint.y() - tl.y());
            break;
        default:
            break;
        }

        setGeometry(target);
    }
}
