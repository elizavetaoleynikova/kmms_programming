#include "keyboard_button.hpp"

#include <QFont>
#include <QSizePolicy>

using biv::KeyBoardButton;

KeyBoardButton::KeyBoardButton(const QString& text, QWidget* parent)
    : QPushButton(parent) {
    setFont(QFont("Roboto", 20));
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // кнопки не забирают фокус, иначе пробел/Enter будут "нажимать" их сами
    setFocusPolicy(Qt::NoFocus);
}
