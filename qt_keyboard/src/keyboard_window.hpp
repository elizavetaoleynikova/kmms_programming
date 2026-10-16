#pragma once

#include <QKeyEvent>
#include <QTextEdit>
#include <QWidget>

#include "keyboard.hpp"

namespace biv {
    class KeyBoardWindow : public QWidget {
        Q_OBJECT

    private:
        QTextEdit* display;
        KeyBoard* keyboard;

    public:
        KeyBoardWindow(QWidget* parent = nullptr);

    signals:
        void welcome_requested();

    protected:
        void keyPressEvent(QKeyEvent* event) override;

    private slots:
        void add_symbol(const QString& text);
        void add_space();
        void add_new_line();
        void remove_symbol();
    };
}
