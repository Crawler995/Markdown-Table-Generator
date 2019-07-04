#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QPoint>
#include <QMouseEvent>

class TitleBar : public QWidget {
    Q_OBJECT
public:
    explicit TitleBar(const QString &appName, QWidget *parent);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QLabel *titleLabel;
    QPushButton *minBtn, *maxBtn, *closeBtn;
    QHBoxLayout *layout;

    bool isMouseLeftBtnPressDown;
    QPoint startDragPoint;

protected slots:
    void minuimize();
    void close();
    void maximize();
};

#endif // TITLEBAR_H
