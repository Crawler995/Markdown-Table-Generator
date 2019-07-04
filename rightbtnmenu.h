#ifndef RIGHTBTNMENU_H
#define RIGHTBTNMENU_H

#include <QWidget>
#include <QMenu>
#include <QAction>

class RightBtnMenu : public QMenu{
    Q_OBJECT
public:
    RightBtnMenu(QWidget *parent = 0);

    QAction *addTopLineAction,
            *addBottomLineAction,
            *addLeftLineAction,
            *addRightLineAction,
            *deleteRowAction,
            *deleteColAction,
            *colAlignCenterAction,
            *colAlignLeftAction,
            *colAlignRightAction,
            *allAlignCenterAction,
            *allAlignLeftAction,
            *allAlignRightAction,
            *clearAllAction;

private:
    QMenu *addLineMenu,
          *deleteLineMenu,
          *colAlignMenu,
          *globalMenu;
};

#endif // RIGHTBTNMENU_H
