#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QString>

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString &text, QWidget *parent = 0);

};

#endif // BUTTON_H
