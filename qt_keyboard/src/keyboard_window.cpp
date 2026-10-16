#include "keyboard_window.hpp"

#include <QFont>
#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QTextCursor>
#include <QVBoxLayout>

using biv::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
    const int keyboard_width = 1160;
    resize(keyboard_width, 760);
    setWindowTitle("Грустная Клавиатура");
    setFocusPolicy(Qt::StrongFocus);

    // верхняя строка: смайлик + кнопка "Назад"
    QHBoxLayout* top_layout = new QHBoxLayout();

    QPixmap pixmap("img/images.jpg");
    if (!pixmap.isNull()) {
        QLabel* image = new QLabel(this);
        image->setFixedSize(150, 150);
        image->setPixmap(pixmap);
        image->setScaledContents(true);
        top_layout->addWidget(image);

    }

    top_layout->addStretch();


    // поле вывода
    display = new QTextEdit();
    display->setMinimumHeight(120);
    display->setMaximumHeight(160);
    display->setFont(QFont("Roboto", 32));
    display->setReadOnly(true);
    display->setFocusPolicy(Qt::NoFocus);
    display->setPlaceholderText("Помоги мне заработать лучше...");

    keyboard = new KeyBoard(keyboard_width);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->addLayout(top_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);

    // сигналы клавиатуры (и мышка, и физические клавиши) -> слоты окна
    connect(keyboard, &KeyBoard::symbol_clicked, this, &KeyBoardWindow::add_symbol);
    connect(keyboard, &KeyBoard::space_clicked, this, &KeyBoardWindow::add_space);
    connect(keyboard, &KeyBoard::enter_clicked, this, &KeyBoardWindow::add_new_line);
    connect(keyboard, &KeyBoard::backspace_clicked, this, &KeyBoardWindow::remove_symbol);

  
}

void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    if (event->modifiers() & (Qt::ControlModifier | Qt::AltModifier)) {
        QWidget::keyPressEvent(event);
        return;
    }
    if (event->key() == Qt::Key_CapsLock) {
        if (!event->isAutoRepeat()) {
            keyboard->toggle_caps_lock();
        }
        return;
    }

    int code = event->key();
    if (code == Qt::Key_Enter) {         // Enter на цифровой клавиатуре
        code = Qt::Key_Return;
    }

    const bool is_special = code == Qt::Key_Backspace
        || code == Qt::Key_Return
        || code == Qt::Key_Space;
    if (!is_special) {
        // буквы и цифры определяем по физической клавише,
        // поэтому работает при любой раскладке
        code = event->nativeVirtualKey();
    }

    if (keyboard->has_key(code)) {
        keyboard->press_key(code);
    }
    else {
        QWidget::keyPressEvent(event);
    }
}

// ----------------------------------------------------------------------------
//                                   SLOTS
// ----------------------------------------------------------------------------
void KeyBoardWindow::add_symbol(const QString& text) {
    display->moveCursor(QTextCursor::End);
    display->insertPlainText(text);
}

void KeyBoardWindow::add_space() {
    add_symbol(" ");
}

void KeyBoardWindow::add_new_line() {
    add_symbol("\n");
}

void KeyBoardWindow::remove_symbol() {
    display->moveCursor(QTextCursor::End);
    display->textCursor().deletePreviousChar();
}
