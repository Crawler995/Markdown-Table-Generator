#include "titlebar.h"
#include "colorboard.h"
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QIcon>
#include <QPixmap>
#include <QPoint>
#include <QMouseEvent>

TitleBar::TitleBar(const QString &appName, QWidget *parent) : QWidget(parent) {
    isMouseLeftBtnPressDown = false;

    titleLabel = new QLabel(appName, this);
    minBtn = new QPushButton(this);
    maxBtn = new QPushButton(this);
    closeBtn = new QPushButton(this);

    setFixedHeight(40);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    minBtn->setFixedSize(30, 30);
    maxBtn->setFixedSize(30, 30);
    closeBtn->setFixedSize(30, 30);

    minBtn->setIcon(QIcon(QPixmap(":/icon/icon/minus.png")));
    maxBtn->setIcon(QIcon(QPixmap(":/icon/icon/border.png")));
    closeBtn->setIcon(QIcon(QPixmap(":/icon/icon/close.png")));

    connect(minBtn, SIGNAL(clicked(bool)), this, SLOT(minuimize()));
    connect(maxBtn, SIGNAL(clicked(bool)), this, SLOT(maximize()));
    connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(close()));

    layout = new QHBoxLayout(this);
    layout->addWidget(titleLabel);
    layout->addWidget(minBtn);
    layout->addWidget(maxBtn);
    layout->addWidget(closeBtn);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    const QString styles = "QPushButton{background-color: " + ColorBoard::white + "; border: 0px;}"
                           "QPushButton:hover{background-color: " + ColorBoard::orange + ";}"
                           "QPushButton:pressed{background-color: " + ColorBoard::darkerOrange + ";}";
    setStyleSheet(styles);
}

void TitleBar::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        isMouseLeftBtnPressDown = true;
        startDragPoint = event->globalPos();
    }
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        isMouseLeftBtnPressDown = false;
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event) {
    if(!isMouseLeftBtnPressDown || window()->isMaximized()) {
        return;
    }

    parentWidget()->move(parentWidget()->geometry().topLeft() + event->globalPos() - startDragPoint);
    startDragPoint = event->globalPos();
}

void TitleBar::minuimize() {
    window()->showMinimized();
}

void TitleBar::maximize() {
    window()->isMaximized() ? window()->showNormal() : window()->showMaximized();
}

void TitleBar::close() {
    window()->close();
}
