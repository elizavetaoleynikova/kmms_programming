#include <QApplication>

#include "keyboard_window.hpp"
#include "welcome_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    biv::WelcomeWindow welcome_window;
    biv::KeyBoardWindow keyboard_window;

    // Приветствие -> клавиатура

    QObject::connect(&welcome_window, &biv::WelcomeWindow::keyboard_requested,&welcome_window,
        [&welcome_window, &keyboard_window]() {
            welcome_window.hide();
            keyboard_window.show();
        }
    );

    welcome_window.show();

    return app.exec();
}
