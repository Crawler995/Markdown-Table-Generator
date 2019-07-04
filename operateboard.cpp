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
    generateMarkdownTextToClipBoardBtn = new Button(tr("导出至剪贴板"), this);
}

Button *OperateBoard::getGenerateMarkdownTextToClipBoardBtn() const
{
    return generateMarkdownTextToClipBoardBtn;
}
