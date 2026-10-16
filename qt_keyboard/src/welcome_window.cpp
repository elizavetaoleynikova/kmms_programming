#include "welcome_window.hpp"

#include <QFont>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using biv::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
    resize(700, 350);
    setWindowTitle("Добро пожаловать");

    QLabel* title = new QLabel("Добро пожаловать в\n«Грустную Клавиатуру»", this);
    title->setFont(QFont("Roboto", 28));
    title->setAlignment(Qt::AlignCenter);

    QPushButton* go_btn = new QPushButton("Перейти к клавиатуре", this);
    go_btn->setFont(QFont("Roboto", 20));
    go_btn->setMinimumHeight(70);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(40, 30, 40, 40);
    layout->addWidget(title, 1);
    layout->addWidget(go_btn);

    // сигнал кнопки -> сигнал окна
    connect(go_btn, &QPushButton::clicked, this, &WelcomeWindow::keyboard_requested);
}
