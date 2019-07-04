#include "rightbtnmenu.h"
#include "colorboard.h"
#include <QMenu>
#include <QWidget>
#include <QAction>
#include <QIcon>
#include <QPixmap>

RightBtnMenu::RightBtnMenu(QWidget *parent) : QMenu(parent) {
    addTopLineAction = new QAction(QIcon(QPixmap(":/icon/icon/add-top-line.png")),
                                   tr("在上面添加行"),
                                   this);
    addBottomLineAction = new QAction(QIcon(QPixmap(":/icon/icon/add-bottom-line.png")),
                                   tr("在下面添加行"),
                                   this);
    addLeftLineAction = new QAction(tr("在左边添加列"), this);
    addRightLineAction = new QAction(tr("在右边添加列"), this);


    deleteRowAction = new QAction(tr("删除此行"), this);
    deleteColAction = new QAction(tr("删除此列"), this);

    colAlignCenterAction = new QAction(QIcon(QPixmap(":/icon/icon/col-align-center.png")),
                                   tr("居中"),
                                   this);
    colAlignLeftAction = new QAction(QIcon(QPixmap(":/icon/icon/col-align-left.png")),
                                   tr("左对齐"),
                                   this);
    colAlignRightAction = new QAction(QIcon(QPixmap(":/icon/icon/col-align-right.png")),
                                   tr("右对齐"),
                                   this);
    allAlignCenterAction = new QAction(QIcon(QPixmap(":/icon/icon/global-align-center.png")),
                                   tr("居中"),
                                   this);
    allAlignLeftAction = new QAction(QIcon(QPixmap(":/icon/icon/global-align-left.png")),
                                   tr("左对齐"),
                                   this);
    allAlignRightAction = new QAction(QIcon(QPixmap(":/icon/icon/global-align-right.png")),
                                   tr("右对齐"),
                                   this);
    clearAllAction = new QAction(tr("清空"), this);

    addLineMenu = addMenu(tr("添加..."));
    deleteLineMenu = addMenu(tr("删除..."));
    colAlignMenu = addMenu(tr("将此列内容..."));
    globalMenu = addMenu(tr("所有单元格..."));

    addLineMenu->addAction(addTopLineAction);
    addLineMenu->addAction(addBottomLineAction);
    addLineMenu->addAction(addLeftLineAction);
    addLineMenu->addAction(addRightLineAction);

    deleteLineMenu->addAction(deleteRowAction);
    deleteLineMenu->addAction(deleteColAction);

    colAlignMenu->addAction(colAlignLeftAction);
    colAlignMenu->addAction(colAlignCenterAction);
    colAlignMenu->addAction(colAlignRightAction);

    globalMenu->addAction(allAlignLeftAction);
    globalMenu->addAction(allAlignCenterAction);
    globalMenu->addAction(allAlignRightAction);
    globalMenu->addSeparator();
    globalMenu->addAction(clearAllAction);

    setStyleSheet("QMenu{background-color: " + ColorBoard::white + ";}"
                  "QMenu::item{background-color: " + ColorBoard::white + "; padding: 5px 30px 5px 30px;}"
                  "QMenu::item:selected{background-color: #e8e8e8; color: #000000;}"
                  "QMenu::icon{padding-left: 8px;}");
}
