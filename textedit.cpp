#include "textedit.h"
#include "colorboard.h"
#include <QWidget>
#include <QTextEdit>
#include <QTextCursor>
#include <QDebug>

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent) {
    setStyleSheet("QTextEdit{border: 2px solid " + ColorBoard::orange + ";"
                  "}");

    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    //setReadOnly(true);

    connect(this, SIGNAL(textChanged()), this, SLOT(textChanged()));
}

void TextEdit::textChanged() {
    emit textEditContentChanged(toPlainText());
}

void TextEdit::changeTextEditContent(const QString &content) {
    setText(content);
    moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
}
