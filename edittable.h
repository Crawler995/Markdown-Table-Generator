#ifndef EDITTABLE_H
#define EDITTABLE_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include <QVector>
#include <QClipboard>
#include "tableitemborder.h"
#include "rightbtnmenu.h"

class EditTable : public QTableWidget {
    Q_OBJECT

public:
    explicit EditTable(int row, int col, QWidget *parent = 0);

private:
    TableItemBorder *border;
    RightBtnMenu *menu;
    int preScrollBarMoveDisX;
    int preScrollBarMoveDisY;
    bool hasTableTitle;
    QVector<Qt::Alignment> aligns;
    QClipboard *clipBoard;

    const int ITEM_BORDER_WIDTH;
    const Qt::Alignment DEFAULT_ALIGN;


    void connectSlots();
    void initAllItemContent();
    void initRowItemContent(int row);
    void initColItemContent(int col);
    void initStyle();
    void moveAnimation(int row, int col);
    QRect getItemBorderRect(int row, int col);
    bool isAllColAlignSame();
    void colAlign(const Qt::Alignment &align);
    void allAlign(const Qt::Alignment &align);
    QString generateMarkdownText();
    int getMostRightNotEmptyCol();
    int getMostBottomNotEmptyRow();

private slots:
    void drawBorderOfSelectedItem(int nextRow, int nextCol, int preRow, int preCol);
    void dynamicChangeTableItemSize(int logicalIndex, int oldSize, int newSize);
    void dynamicChangeTableItemBorderPosX(int dis);
    void dynamicChangeTableItemBorderPosY(int dis);
    void menuPopuped(const QPoint &pos);

    void addTopLine();
    void addBottomLine();
    void addLeftLine();
    void addRightLine();
    void deleteRow();
    void deleteCol();

    void colAlignLeft();
    void colAlignCenter();
    void colAlignRight();
    void allAlignLeft();
    void allAlignCenter();
    void allAlignRight();

    void clearAll();

    void changeCurrentItemContent(const QString &content);
    void alignCurEditedItem(int row, int col);

    void generateMarkdownTextToClipBoard();

signals:
    void itemContentChanged(const QString &content);
};

#endif // EDITTABLE_H
