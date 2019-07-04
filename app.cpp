#include "app.h"
#include "mainwindow.h"
#include "workarea.h"
#include <QFont>

App::App(QWidget *parent) : MainWindow(parent) {
    setFont(QFont("Microsoft Yahei"));

    workArea = new WorkArea(this);
    initWindowComponent(workArea);
}

App::~App() {}
