#include "tableitemborder.h"
#include "colorboard.h"
#include <QLabel>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QColor>
#include <QPen>

TableItemBorder::TableItemBorder(int strokeWidth, QWidget *parent) : QLabel(parent) {
    this->strokeWidth = strokeWidth;

    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void TableItemBorder::paintEvent(QPaintEvent *event) {
    QLabel::paintEvent(event);
    QPainter painter(this);
    painter.setPen(QPen(QColor(ColorBoard::orange), strokeWidth * 2));
    painter.drawRect(QRect(0, 0, width(), height()));
}
