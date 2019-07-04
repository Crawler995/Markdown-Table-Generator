#include "button.h"
#include "colorboard.h"
#include <QPushButton>
#include <QWidget>
#include <QString>

Button::Button(const QString &text, QWidget *parent) : QPushButton(text, parent)
{
    const QString styles = "QPushButton{background-color: " + ColorBoard::orange + "; border: 0px; color: white; padding: 10px; border-radius: 4px;}"
                           "QPushButton:hover{background-color: " + ColorBoard::darkOrange + ";}"
                           "QPushButton:pressed{background-color: " + ColorBoard::darkerOrange + ";}";
    setStyleSheet(styles);
}
