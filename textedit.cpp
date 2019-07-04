#include "textedit.h"
#include "colorboard.h"
#include <QWidget>
#include <QTextEdit>

TextEdit::TextEdit(QWidget *parent) : QTextEdit(parent) {
    setStyleSheet("QTextEdit{border: 2px solid " + ColorBoard::orange + ";"
                  "}");
}
