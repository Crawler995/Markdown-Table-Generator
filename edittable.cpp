#include "edittable.h"
#include "colorboard.h"
#include "nofocusdelegate.h"
#include "tableitemborder.h"
#include "rightbtnmenu.h"
#include <QTableWidget>
#include <QWidget>
#include <QString>
#include <QHeaderView>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QFontMetrics>
#include <QPoint>
#include <QBrush>
#include <QClipboard>
#include <QGuiApplication>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <QFile>
#include <QDebug>

EditTable::EditTable(int row, int col, QWidget *parent) :
    QTableWidget(row, col, parent),
    ITEM_BORDER_WIDTH(2),
    DEFAULT_ALIGN(Qt::AlignLeft | Qt::AlignVCenter) {

    setShowGrid(false);
    // hide the focus dotted border
    setItemDelegate(new NoFocusDelegate());
    setSelectionMode(QAbstractItemView::SingleSelection);
    // scroll smoothly
    setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    // use the custom menu
    setContextMenuPolicy(Qt::CustomContextMenu);
    horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    verticalHeader()->setDefaultAlignment(Qt::AlignCenter);
    horizontalHeader()->setMinimumHeight(30);
    verticalHeader()->setMinimumWidth(30);
    horizontalHeader()->setSectionsClickable(false);
    verticalHeader()->setSectionsClickable(false);
    // unable the top left clickable area
    setCornerButtonEnabled(false);

    initStyle();
    initAllItemContent();

    menu = new RightBtnMenu(this);
    border = nullptr;
    // use to move the item border when scroll bar moved
    preScrollBarMoveDisX = preScrollBarMoveDisY = 0;

    for(int i = 0; i < columnCount(); i++) {
        aligns.append(DEFAULT_ALIGN);
    }

    connectSlots();
}

void EditTable::connectSlots() {
    // when change the selection of table item
    // draw the table item border and create the gradient animation
    connect(this, SIGNAL(currentCellChanged(int,int,int,int)),
            this, SLOT(drawBorderOfSelectedItem(int,int,int,int)));
    connect(this, SIGNAL(cellChanged(int,int)),
            this, SLOT(alignCurEditedItem(int, int)));
    // scroll the horizontal bar
    // move the table item border
    connect(qobject_cast<QWidget*>(this->horizontalScrollBar()), SIGNAL(valueChanged(int)),
            this, SLOT(dynamicChangeTableItemBorderPosX(int)));
    // scroll the vertical bar
    // move the table item border
    connect(qobject_cast<QWidget*>(this->verticalScrollBar()), SIGNAL(valueChanged(int)),
            this, SLOT(dynamicChangeTableItemBorderPosY(int)));
    // drag the horizontal header to change the column width
    // move the table item border
    connect(this->horizontalHeader(), SIGNAL(sectionResized(int,int,int)),
            this, SLOT(dynamicChangeTableItemSize(int,int,int)));
    // drag the vertical header to change the row height
    // move the table item border
    connect(this->verticalHeader(), SIGNAL(sectionResized(int,int,int)),
            this, SLOT(dynamicChangeTableItemSize(int,int,int)));
    // mouse right button clicked
    // popup the menu
    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(menuPopuped(QPoint)));

    // connect signals and slots of menu
    connect(menu->addTopLineAction, SIGNAL(triggered(bool)),
            this, SLOT(addTopLine()));
    connect(menu->addBottomLineAction, SIGNAL(triggered(bool)),
            this, SLOT(addBottomLine()));
    connect(menu->addLeftLineAction, SIGNAL(triggered(bool)),
            this, SLOT(addLeftLine()));
    connect(menu->addRightLineAction, SIGNAL(triggered(bool)),
            this, SLOT(addRightLine()));
    connect(menu->deleteRowAction, SIGNAL(triggered(bool)),
            this, SLOT(deleteRow()));
    connect(menu->deleteColAction, SIGNAL(triggered(bool)),
            this, SLOT(deleteCol()));
    connect(menu->colAlignLeftAction, SIGNAL(triggered(bool)),
            this, SLOT(colAlignLeft()));
    connect(menu->colAlignCenterAction, SIGNAL(triggered(bool)),
            this, SLOT(colAlignCenter()));
    connect(menu->colAlignRightAction, SIGNAL(triggered(bool)),
            this, SLOT(colAlignRight()));
    connect(menu->allAlignLeftAction, SIGNAL(triggered(bool)),
            this, SLOT(allAlignLeft()));
    connect(menu->allAlignCenterAction, SIGNAL(triggered(bool)),
            this, SLOT(allAlignCenter()));
    connect(menu->allAlignRightAction, SIGNAL(triggered(bool)),
            this, SLOT(allAlignRight()));

    connect(menu->clearAllAction, SIGNAL(triggered(bool)),
            this, SLOT(clearAll()));
}

void EditTable::initAllItemContent() {
    for(int i = 0; i < rowCount(); i++) {
        for(int j = 0; j < columnCount(); j++) {
            setItem(i, j, new QTableWidgetItem(""));
        }
    }
}

void EditTable::initRowItemContent(int row) {
    for(int i = 0; i < columnCount(); i++) {
        setItem(row, i, new QTableWidgetItem(""));
    }
}

void EditTable::initColItemContent(int col) {
    for(int i = 0; i < rowCount(); i++) {
        setItem(i, col, new QTableWidgetItem(""));
    }
}

void EditTable::initStyle() {
    setStyleSheet("QHeaderView{background-color: " + ColorBoard::orange + "; color: " + ColorBoard::white + ";}"
                  "QHeaderView::section{background-color: " + ColorBoard::orange + "; border: none;}"
                  "QTableWidget{background: transparent; border: " + QString::number(ITEM_BORDER_WIDTH) + "px solid " + ColorBoard::orange + ";}"
                  "QTableWidget::item{background: transparent; border-bottom: " + QString::number(ITEM_BORDER_WIDTH) + "px solid " + ColorBoard::gray + ";"
                  "border-right: " + QString::number(ITEM_BORDER_WIDTH) + "px solid " + ColorBoard::gray + ";}"
                  "QTableWidget::item:selected{color: black;}"
                  "QTableView QTableCornerButton::section{background-color: " + ColorBoard::orange + ";}");

    horizontalHeader()->setStyleSheet("QHeaderView::section{border-right: 2px solid " + ColorBoard::lightGray + ";}");
    verticalHeader()->setStyleSheet("QHeaderView::section{border-bottom: 2px solid " + ColorBoard::lightGray + ";}");

    horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:" + ColorBoard::lightGray + "; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:" + ColorBoard::gray + ";}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
}

void EditTable::moveAnimation(int row, int col) {
    QPropertyAnimation *ani = new QPropertyAnimation(border, "geometry");
    ani->setDuration(200);

    ani->setEndValue(getItemBorderRect(row, col));
    ani->setEasingCurve(QEasingCurve::OutCubic);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
}

QRect EditTable::getItemBorderRect(int row, int col) {
    int x = verticalHeader()->width();
    for(int i = 0; i < col; i++) {
        x += columnWidth(i);
    }
    x -= horizontalScrollBar()->value();

    int y = horizontalHeader()->height();
    for(int i = 0; i < row; i++) {
        y += rowHeight(i);
    }
    y -= verticalScrollBar()->value();

    int width = columnWidth(col) + ITEM_BORDER_WIDTH;
    int height = rowHeight(row) + ITEM_BORDER_WIDTH;

    return QRect(x, y, width, height);
}

bool EditTable::isAllColAlignSame() {
    for(auto i = aligns.constBegin(); i < aligns.constEnd() - 1; i++) {
        if(*i != *(i + 1)) {
            return false;
        }
    }
    return true;
}

void EditTable::colAlign(const Qt::Alignment &align) {
    int col = currentColumn();
    aligns[col] = align;
    for(int i = 0; i < rowCount(); i++) {
        if(item(i, col) == 0) continue;
        item(i, col)->setTextAlignment(align);
    }
}

void EditTable::allAlign(const Qt::Alignment &align) {
    for(int i = 0; i < columnCount(); i++) {
        aligns[i] = align;
        for(int j = 0; j < rowCount(); j++) {
            if(item(j, i) == 0) continue;
            item(j, i)->setTextAlignment(align);
        }
    }
}

QString EditTable::generateMarkdownText() {
    QString titlesMarkdownText;
    QString alignsMarkdownText;
    QString itemsMarkdownText;
    QString res;

    int mostRightNotEmptyCol = getMostRightNotEmptyCol();
    int mostBottomNotEmptyRow = getMostBottomNotEmptyRow();

    if(mostRightNotEmptyCol == 0 && mostBottomNotEmptyRow == 0) {
        return "";
    }

    for(int i = 0; i < mostRightNotEmptyCol; i++) {
        titlesMarkdownText += "| " + (item(0, i) ? item(0, i)->text() : "") + " ";
    }
    titlesMarkdownText += "|";

    for(int i = 0; i < mostRightNotEmptyCol; i++) {
        QString alignMarkDownText;
        Qt::Alignment itemAlign = aligns[i];

        if(itemAlign == (Qt::AlignLeft | Qt::AlignVCenter)) {
            alignMarkDownText = ":-";
        }
        else if(itemAlign == (Qt::AlignRight | Qt::AlignVCenter)) {
            alignMarkDownText = "-:";
        }
        else if(itemAlign == (Qt::AlignHCenter | Qt::AlignVCenter)) {
            alignMarkDownText = ":-:";
        }

        alignsMarkdownText += "| " + alignMarkDownText + " ";
    }
    alignsMarkdownText += "|";

    for(int i = 1; i < mostBottomNotEmptyRow; i++) {
        for(int j = 0; j < mostRightNotEmptyCol; j++) {
            itemsMarkdownText += "| " + (item(i, j) ? item(i, j)->text() : "") + " ";
        }
        itemsMarkdownText += "|\n";
    }

    res = titlesMarkdownText + "\n" + alignsMarkdownText + "\n" + itemsMarkdownText;

    return res;
}

int EditTable::getMostRightNotEmptyCol() {
    int res = -1;

    for(int i = 0; i < rowCount(); i++) {
        int tmp = -1;
        for(int j = 0; j < columnCount(); j++) {
            if(item(i, j) && item(i, j)->text() != "") {
                tmp = j;
            }
        }
        res = res > tmp ? res : tmp;
    }

    return res + 1;
}

int EditTable::getMostBottomNotEmptyRow() {
    int res = -1;

    for(int i = 0; i < columnCount(); i++) {
        int tmp = -1;
        for(int j = 0; j < rowCount(); j++) {
            if(item(j, i) && item(j, i)->text() != "") {
                tmp = j;
            }
        }
        res = res > tmp ? res : tmp;
    }

    return res + 1;
}

void EditTable::drawBorderOfSelectedItem(int nextRow, int nextCol, int preRow, int preCol) {
    // first click the table item
    if(!border) {
        border = new TableItemBorder(ITEM_BORDER_WIDTH * 2, this);
        border->setGeometry(getItemBorderRect(nextRow, nextCol));
        border->show();
    }

    emit itemContentChanged(QString(item(nextRow, nextCol) ?
                                    item(nextRow, nextCol)->text() :
                                    "").replace("<br>", "\n"));

    moveAnimation(nextRow, nextCol);
}

void EditTable::dynamicChangeTableItemSize(int logicalIndex, int oldSize, int newSize) {
    int curRow = this->currentRow();
    int curCol = this->currentColumn();

    border->setGeometry(getItemBorderRect(curRow, curCol));
}

void EditTable::dynamicChangeTableItemBorderPosX(int dis) {
    int tmp = dis;
    dis -= preScrollBarMoveDisX;
    preScrollBarMoveDisX = tmp;
    border->move(border->x() - dis, border->y());
}

void EditTable::dynamicChangeTableItemBorderPosY(int dis) {
    int tmp = dis;
    dis -= preScrollBarMoveDisY;
    preScrollBarMoveDisY = tmp;
    border->move(border->x(), border->y() - dis);
}

void EditTable::menuPopuped(const QPoint &pos) {
    menu->popup(QCursor::pos());
}

void EditTable::addTopLine() {
    if(currentRow() != -1) {
        insertRow(currentRow());
        initRowItemContent(currentRow() - 1);
        moveAnimation(currentRow(), currentColumn());
    }
    else {
        insertRow(0);
        initRowItemContent(0);
        setCurrentCell(0, 0);
    }

}
void EditTable::addBottomLine() {
    bool currentCellVisible = currentRow() != -1;
    insertRow(currentRow() + 1);
    initRowItemContent(currentRow() + 1);
    if(!currentCellVisible) {
        setCurrentCell(0, 0);
    }
    else {
        moveAnimation(currentRow(), currentColumn());
    }
}
void EditTable::addLeftLine() {
    if(currentColumn() != -1) {
        aligns.insert(currentColumn(), isAllColAlignSame() ?
                                       (aligns.length() > 0 ? aligns[0] : DEFAULT_ALIGN) :
                                       DEFAULT_ALIGN);
        insertColumn(currentColumn());
        initColItemContent(currentColumn() - 1);
        moveAnimation(currentRow(), currentColumn());
    }
    else {
        aligns.insert(0, DEFAULT_ALIGN);
        insertColumn(0);
        initColItemContent(0);
        setCurrentCell(0, 0);
    }
}
void EditTable::addRightLine() {
    bool currentCellVisible = currentColumn() != -1;
    aligns.insert(currentColumn() + 1, isAllColAlignSame() ?
                                       (aligns.length() > 0 ? aligns[0] : DEFAULT_ALIGN) :
                                       DEFAULT_ALIGN);
    insertColumn(currentColumn() + 1);

    initColItemContent(currentColumn() + 1);
    if(!currentCellVisible) {
        setCurrentCell(0, 0);
    }
    else {
        moveAnimation(currentRow(), currentColumn());
    }
}
void EditTable::deleteRow() {
    removeRow(currentRow());
    moveAnimation(currentRow(), currentColumn());
}
void EditTable::deleteCol() {
    int col = currentColumn();
    int flag = currentColumn() == columnCount() - 1;
    aligns.remove(currentColumn());

    removeColumn(currentColumn());
    setCurrentCell(currentRow(), col - flag);
    moveAnimation(currentRow(), col - flag);
}

void EditTable::colAlignLeft() {
    colAlign(Qt::AlignLeft | Qt::AlignVCenter);
}

void EditTable::colAlignCenter() {
    colAlign(Qt::AlignHCenter | Qt::AlignVCenter);
}

void EditTable::colAlignRight() {
    colAlign(Qt::AlignRight | Qt::AlignVCenter);
}

void EditTable::allAlignLeft() {
    allAlign(Qt::AlignLeft | Qt::AlignVCenter);
}

void EditTable::allAlignCenter() {
    allAlign(Qt::AlignHCenter | Qt::AlignVCenter);
}

void EditTable::allAlignRight() {
    allAlign(Qt::AlignRight | Qt::AlignVCenter);
}

void EditTable::clearAll() {
    for(int i = 0; i < rowCount(); i++) {
        for(int j = 0; j < columnCount(); j++) {
            if(item(i, j) == 0) continue;
            item(i, j)->setText("");
        }
    }
    allAlign(DEFAULT_ALIGN);
}

void EditTable::changeCurrentItemContent(const QString &content) {
    if(currentItem()) {
        currentItem()->setText(QString(content).replace("\n", "<br>"));
    }
}

void EditTable::alignCurEditedItem(int row, int col) {
    item(row, col)->setTextAlignment(aligns[col]);
    if(item(row, col)->text() != "" && item(row, col) == currentItem()) {
        emit itemContentChanged(QString(item(row, col) ? item(row, col)->text() : "").replace("<br>", "\n"));
    }
}

void EditTable::generateMarkdownTextToClipBoard() {
    clipBoard = QGuiApplication::clipboard();
    clipBoard->setText(generateMarkdownText());
}

void EditTable::generateMarkdownTextToFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存为markdown文件"),
                                                    "1.md", "Markdown files(*.md)");
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);
    stream << generateMarkdownText();

    file.close();
}
