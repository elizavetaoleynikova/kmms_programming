#pragma once

#include <QPushButton>
#include <QString>
#include <QWidget>

namespace biv {
    class KeyBoardButton : public QPushButton {
    public:
        KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
    };
}
