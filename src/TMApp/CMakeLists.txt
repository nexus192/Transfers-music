cmake_minimum_required(VERSION 3.21)

project(TMApp VERSION 0.1 LANGUAGES CXX)

file(GLOB TMAppQML
    UI/*.qml
    UI/*/*.qml
    UI/*/*/*.qml
    UI/*/*/*/*.qml
    UI/*/*/*/*/*.qml
)

foreach(QML_FILE ${TMAppQML})
    file(RELATIVE_PATH REL_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${QML_FILE})
    set_source_files_properties(${QML_FILE} PROPERTIES QT_RESOURCE_ALIAS ${REL_PATH})
endforeach()

qt_standard_project_setup(REQUIRES 6.5)

add_library(TMApp STATIC

)

qt_add_qml_module(TMApp
    URI TMApp
    VERSION 1.0
    QML_FILES Main.qml ${TMAppQML}
)

target_include_directories(TMApp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(TMApp PUBLIC
    TMDomain
    Qt6::Quick
    Qt6::Qml
    Qt6::Gui)
