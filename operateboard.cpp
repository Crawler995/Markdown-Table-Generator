#include "operateboard.h"
#include "button.h"
#include "textedit.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollArea>

// input

// header: use or not (single selection)

// align
// selected col: left center right
// all col: left center right

// add: top bottom left right
// delete: top bottom left right

// export: clipboard mdfile

OperateBoard::OperateBoard(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout(this);

    tableItemDataTextEdit = new TextEdit(this);
    generateMarkdownTextToClipBoardBtn = new Button(tr("导出至剪贴板"), this);
    generateMarkdownTextToMDFileBtn = new Button(tr("导出为Markdown文件"), this);

    layout->addWidget(tableItemDataTextEdit);
    layout->addWidget(generateMarkdownTextToClipBoardBtn);
    layout->addWidget(generateMarkdownTextToMDFileBtn);

    setLayout(layout);
}

Button *OperateBoard::getGenerateMarkdownTextToClipBoardBtn() const
{
    return generateMarkdownTextToClipBoardBtn;
}

Button *OperateBoard::getGenerateMarkdownTextToMDFileBtn() const
{
    return generateMarkdownTextToMDFileBtn;
}

TextEdit *OperateBoard::getTableItemDataTextEdit() const
{
    return tableItemDataTextEdit;
}
