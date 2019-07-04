#ifndef OPERATEBOARD_H
#define OPERATEBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QList>
#include "button.h"
#include "textedit.h"

class OperateBoard : public QWidget {
    Q_OBJECT
public:
    explicit OperateBoard(QWidget *parent = 0);

    Button *getGenerateMarkdownTextToClipBoardBtn() const;

private:
    TextEdit *tableItemDataTextEdit;
    Button *generateMarkdownTextToClipBoardBtn;

};

#endif // OPERATEBOARD_H
