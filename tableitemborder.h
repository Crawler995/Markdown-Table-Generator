#ifndef TABLEITEMBORDER_H
#define TABLEITEMBORDER_H

#include <QLabel>
#include <QWidget>
#include <QPaintEvent>

class TableItemBorder : public QLabel
{
    Q_OBJECT
public:
    explicit TableItemBorder(int strokeWidth, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);

private:
    int strokeWidth;
};

#endif // TABLEITEMBORDER_H
