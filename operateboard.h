#ifndef OPERATEBOARD_H
#define OPERATEBOARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "button.h"
#include "textedit.h"

class OperateBoard : public QWidget {
    Q_OBJECT
public:
    explicit OperateBoard(QWidget *parent = 0);

    Button *getGenerateMarkdownTextToClipBoardBtn() const;
    Button *getGenerateMarkdownTextToMDFileBtn() const;
    Button *getOpenGuideBtn() const;
    TextEdit *getTableItemDataTextEdit() const;

private:
    QVBoxLayout *layout;
    TextEdit *tableItemDataTextEdit;
    Button *openGuideBtn,
           *generateMarkdownTextToClipBoardBtn,
           *generateMarkdownTextToMDFileBtn;
};

#endif // OPERATEBOARD_H
