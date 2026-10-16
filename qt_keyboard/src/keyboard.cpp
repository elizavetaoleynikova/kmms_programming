#include "keyboard.hpp"

#include <QTimer>

using biv::KeyBoard;
using biv::KeyBoardButton;

KeyBoard::KeyBoard(const int width, QWidget* parent)
    : QWidget(parent), button_width(width / 29) {

    QGridLayout* keys_layout = new QGridLayout(this);
    keys_layout->setContentsMargins(0, 0, 0, 0);
    keys_layout->setSpacing(5);

    // 1-я линия
    create_buttons(keyboard_data.get_line1(), keys_layout, 0, 0);
    create_button(Qt::Key_Backspace, "Удалить", keys_layout, 0, 26, 2, 3);

    // 2-я линия
    create_button(0, "Tab", keys_layout, 2, 0, 2, 3);
    create_buttons(keyboard_data.get_line2(), keys_layout, 2, 3);

    // 3-я линия
    create_caps_lock_button(keys_layout, 4, 0, 2, 4);
    create_buttons(keyboard_data.get_line3(), keys_layout, 4, 4);
    create_button(Qt::Key_Return, "Enter", keys_layout, 4, 26, 2, 3);

    // 4-я линия
    create_button(0, "Shift", keys_layout, 6, 0, 2, 5);
    create_buttons(keyboard_data.get_line4(), keys_layout, 6, 5);
    create_button(0, "Shift", keys_layout, 6, 25, 2, 4);

    // 5-я линия
    create_button(Qt::Key_Space, "", keys_layout, 8, 7, 2, 16);
}

bool KeyBoard::has_key(const int code) const noexcept {
    return buttons.find(code) != buttons.end();
}

void KeyBoard::press_key(const int code) {
    auto it = buttons.find(code);
    if (it == buttons.end()) {
        return;
    }

    emit_key(code);

    // визуальный эффект нажатия
    KeyBoardButton* btn = it->second;
    btn->setDown(true);
    QTimer::singleShot(100, btn, [btn]() { btn->setDown(false); });
}

// ----------------------------------------------------------------------------
//                                  PRIVATE
// ----------------------------------------------------------------------------
void KeyBoard::create_buttons(
    const std::vector<KeyData>& data,
    QGridLayout* layout,
    const int line,
    const int start_position
) {
    for (int i = 0; i < static_cast<int>(data.size()); i++) {
        create_button(data[i].code, data[i].text, layout,
            line, i * 2 + start_position, 2, 2);
    }
}

// code == 0 - декоративная кнопка (Tab, Shift), ничего не делает
KeyBoardButton* KeyBoard::create_button(
    const int code,
    const QString& text,
    QGridLayout* layout,
    const int row, const int column,
    const int row_span, const int column_span
) {
    KeyBoardButton* btn = new KeyBoardButton(text);
    btn->setMinimumSize(button_width * column_span / 2, button_width);
    layout->addWidget(btn, row, column, row_span, column_span);

    if (code != 0) {
        buttons[code] = btn;
        connect(btn, &QPushButton::clicked, this, [this, code]() {
            emit_key(code);
            });
    }
    return btn;
}
// Caps_Lock
KeyBoardButton* KeyBoard::create_caps_lock_button(
    QGridLayout* layout,
    const int row, const int column,
    const int row_span, const int column_span
) {
    KeyBoardButton* btn = new KeyBoardButton("Caps");
    btn->setMinimumSize(button_width * column_span / 2, button_width);
    layout->addWidget(btn, row, column, row_span, column_span);

    //buttons[Qt::Key_CapsLock] = btn;

    connect(btn, &QPushButton::clicked, this, [this]() {
        toggle_caps_lock();
        });

    return btn;
}

void KeyBoard::toggle_caps_lock() {
    caps_lock = !caps_lock;
}

void KeyBoard::emit_key(const int code) {
    switch (code) {
    case Qt::Key_Backspace:
        emit backspace_clicked();
        break;

    case Qt::Key_Return:
        emit enter_clicked();
        break;

    case Qt::Key_Space:
        emit space_clicked();
        break;

   
    default: {
        QString text = buttons.at(code)->text();

        if (caps_lock) {
            text = text.toUpper();
        }
        else {
            text = text.toLower();
        }

        emit symbol_clicked(text);
        break;
    }
    }
}
