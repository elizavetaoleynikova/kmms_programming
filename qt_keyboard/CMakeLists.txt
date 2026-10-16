cmake_minimum_required(VERSION 3.16)

project(grustnaya_klaviatura VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(grustnaya_klaviatura
    src/main.cpp
    src/key_data.hpp
    src/keyboard_data.cpp
    src/keyboard_data.hpp
    src/keyboard_button.cpp
    src/keyboard_button.hpp
    src/keyboard.cpp
    src/keyboard.hpp
    src/keyboard_window.cpp
    src/keyboard_window.hpp
    src/welcome_window.cpp
    src/welcome_window.hpp
)

target_link_libraries(grustnaya_klaviatura
    PRIVATE Qt6::Widgets
)

# Копирование папки img рядом с исполняемым файлом
add_custom_command(TARGET grustnaya_klaviatura POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/img"
            "$<TARGET_FILE_DIR:grustnaya_klaviatura>/img"
)