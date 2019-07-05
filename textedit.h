#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QTextEdit>
#include <QString>

class TextEdit : public QTextEdit {
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);

protected slots:
    void textChanged();

private slots:
    void changeTextEditContent(const QString &content);

signals:
    void textEditContentChanged(const QString &content);
};

#endif // TEXTEDIT_H
