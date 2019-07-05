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
    openGuideBtn = new Button(tr("查看帮助"), this);
    generateMarkdownTextToClipBoardBtn = new Button(tr("导出至剪贴板"), this);
    generateMarkdownTextToMDFileBtn = new Button(tr("导出为Markdown文件"), this);

    layout->addWidget(tableItemDataTextEdit);
    layout->addWidget(openGuideBtn);
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

Button *OperateBoard::getOpenGuideBtn() const
{
    return openGuideBtn;
}

TextEdit *OperateBoard::getTableItemDataTextEdit() const
{
    return tableItemDataTextEdit;
}
