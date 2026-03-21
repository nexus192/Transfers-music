cmake_minimum_required(VERSION 3.16)

project(TMMain VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(transfers_music
    main.cpp
)

target_include_directories(transfers_music PUBLIC
    ${CMAKE_SOURCE_DIR}/src/TMApp
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_link_libraries(transfers_music
    PUBLIC
    TMDomain
    TMAppplugin
    Qt6::Quick
    Qt6::Qml
    Qt6::Widgets
)

qt_import_qml_plugins(TMApp)
