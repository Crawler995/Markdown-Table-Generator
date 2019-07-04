#ifndef APP_H
#define APP_H

#include <QWidget>
#include "mainwindow.h"
#include "workarea.h"

class App : public MainWindow {
    Q_OBJECT

public:
    App(QWidget *parent = 0);
    ~App();

private:
    WorkArea *workArea;
};

#endif // WIDGET_H
