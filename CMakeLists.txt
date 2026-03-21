cmake_minimum_required(VERSION 3.21)
project(Transfers-music LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Wa,-mbig-obj" COMPILER_SUPPORTS_BIG_OBJ)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    Qml
    Widgets
    Core5Compat
)

qt_standard_project_setup(REQUIRES 6.5)

add_subdirectory(src/TMDomain)
add_subdirectory(src/TMApp)
add_subdirectory(src/TMMain)
