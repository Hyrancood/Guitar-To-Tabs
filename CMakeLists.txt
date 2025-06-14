cmake_minimum_required(VERSION 3.14)
project(Guitar-To-Tabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к заголовочным файлам
include_directories(include)

# === Подключение doctest через FetchContent ===
add_subdirectory(external)

# Главная библиотека
add_library(guitar_to_tabs STATIC
    src/frequency_to_midi.cpp
)

# Тесты
enable_testing()

add_executable(test_runner tests/test_frequency_to_midi.cpp)
target_link_libraries(test_runner PRIVATE guitar_to_tabs doctest)

add_test(NAME GuitarToTabsTests COMMAND test_runner)