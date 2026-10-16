#pragma once

#include <unordered_map>
#include <vector>

#include <QGridLayout>
#include <QString>
#include <QWidget>

#include "keyboard_button.hpp"
#include "keyboard_data.hpp"
#include "key_data.hpp"

namespace biv {
    class KeyBoard : public QWidget {
        Q_OBJECT

    private:
        const int button_width;
        std::unordered_map<int, KeyBoardButton*> buttons;
        KeyBoardData keyboard_data;

        bool caps_lock = false;

    public:
        KeyBoard(const int width, QWidget* parent = nullptr);

        bool has_key(const int code) const noexcept;
        // Ќажатие с физической клавиатуры: подсвечивает кнопку
        // и посылает тот же сигнал, что и клик мышкой
        void press_key(const int code);
  
        void toggle_caps_lock();

    signals:
        void symbol_clicked(const QString& text);
        void space_clicked();
        void enter_clicked();
        void backspace_clicked();

    private:
        void create_buttons(
            const std::vector<KeyData>& data,
            QGridLayout* layout,
            const int line,
            const int start_position
        );
        KeyBoardButton* create_button(
            const int code,
            const QString& text,
            QGridLayout* layout,
            const int row, const int column,
            const int row_span, const int column_span
        );

        KeyBoardButton* create_caps_lock_button(
            QGridLayout* layout,
            const int row, const int column,
            const int row_span, const int column_span
        );

        void emit_key(const int code);
    };
}
