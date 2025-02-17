cmake_minimum_required(VERSION 3.16)

project(TrayMusic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia )

file(GLOB_RECURSE PROJECT_SOURCES
        "src/*.cpp"
        "include/*.h"
        "res/*.qrc"
)
file(GLOB_RECURSE UI_FILES
        "ui/*.ui"
)
include_directories("include")

qt_add_executable(TrayMusic
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
)

target_link_libraries(TrayMusic PRIVATE
        Qt6::Widgets
        Qt6::Multimedia
)

set_target_properties(TrayMusic PROPERTIES
        WIN32_EXECUTABLE TRUE
        MACOSX_BUNDLE TRUE
)

include(GNUInstallDirs)

qt_finalize_executable(TrayMusic)