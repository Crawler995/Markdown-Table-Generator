#ifndef WORKAREA_H
#define WORKAREA_H

#include <QWidget>
#include <QGridLayout>
#include "edittable.h"
#include "operateboard.h"

class WorkArea : public QWidget {
    Q_OBJECT
public:
    explicit WorkArea(QWidget *parent = 0);

private:
    QGridLayout *layout;
    EditTable *editTable;
    OperateBoard *operateBoard;
};

#endif // WORKAREA_H
