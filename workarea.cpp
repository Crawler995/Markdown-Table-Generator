#include "workarea.h"
#include <QGridLayout>
#include <QScrollArea>

WorkArea::WorkArea(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    editTable = new EditTable(10, 4, this);

    operateBoard = new OperateBoard(this);

    layout->addWidget(editTable, 0, 0, 1, 2);
    layout->addWidget(operateBoard, 0, 2, 1, 1);

    setLayout(layout);

    connect(operateBoard->getGenerateMarkdownTextToClipBoardBtn(), SIGNAL(clicked(bool)),
            editTable, SLOT(generateMarkdownTextToClipBoard()));
    connect(operateBoard->getTableItemDataTextEdit(), SIGNAL(textEditContentChanged(QString)),
            editTable, SLOT(changeCurrentItemContent(QString)));
    connect(editTable, SIGNAL(itemContentChanged(QString)),
            operateBoard->getTableItemDataTextEdit(),
            SLOT(changeTextEditContent(QString)));
}
