cmake_minimum_required(VERSION 3.5)

project(A429Decoder VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        a429bcdwidget.cpp
        a429bcdwidget.hpp
        a429bnrwidget.cpp
        a429bnrwidget.hpp
        a429bnrwidget.ui
        a429dwwidget.cpp
        a429dwwidget.hpp
        arinc429widget.cpp
        arinc429widget.hpp
        main.cpp
        mainwindow.cpp
        mainwindow.hpp
        a429bcdwidget.ui
        a429dwwidget.ui
        arinc429widget.ui
        mainwindow.ui
        resources.qrc
)

include_directories(../A429Library)
add_library(A429Library STATIC ../A429Library/a429word.hpp ../A429Library/a429word.cpp
                               ../A429Library/a429bnrword.hpp ../A429Library/a429bnrword.cpp
                               ../A429Library/a429bcdword.hpp ../A429Library/a429bcdword.cpp)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(A429Decoder MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    if(ANDROID)
        add_library(A429Decoder SHARED ${PROJECT_SOURCES})
    else()
        add_executable(A429Decoder ${PROJECT_SOURCES})
    endif()
endif()

target_link_libraries(A429Decoder PUBLIC A429Library)

# Since Qt 5.15, the CMake targets are also available as Qt::Core, Qt::Gui, and so on.
# This eases writing CMake code that can work with both Qt 5 and Qt 6.
target_link_libraries(A429Decoder PRIVATE Qt::Widgets)

set_target_properties(A429Decoder PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(A429Decoder)
endif()


#####################################################################
## A429Decoder Binary:
#####################################################################

#qt_internal_add_executable(A429Decoder
#    GUI
#    SOURCES
#        a429bcdwidget.cpp a429bcdwidget.hpp a429bcdwidget.ui
#        a429bnrwidget.cpp a429bnrwidget.hpp a429bnrwidget.ui
#        a429dwwidget.cpp a429dwwidget.hpp a429dwwidget.ui
#        arinc429widget.cpp arinc429widget.hpp arinc429widget.ui
#        main.cpp
#        mainwindow.cpp mainwindow.hpp mainwindow.ui
#    INCLUDE_DIRECTORIES
#        ../A429Library
#    PUBLIC_LIBRARIES
#        Qt::Gui
#    ENABLE_AUTOGEN_TOOLS
#        uic
#)

## Resources:
#set(resources_resource_files
#    "decode128.png"
#    "decode256.png"
#    "decode32.png"
#    "decode512.png"
#    "decode64.png"
#)

#qt_internal_add_resource(A429Decoder "resources"
#    PREFIX
#        "/icons"
#    FILES
#        ${resources_resource_files}
#)


#### Keys ignored in scope 1:.:.:A429Decoder.pro:<TRUE>:
# DEPENDPATH = "$$PWD/../A429Library"

## Scopes:
#####################################################################

#qt_internal_extend_target(A429Decoder CONDITION (QT_MAJOR_VERSION GREATER 4)
#    PUBLIC_LIBRARIES
#        Qt::Widgets
#)

#### Keys ignored in scope 3:.:.:A429Decoder.pro:MACOS:
# ICON = "decode.icns"

#### Keys ignored in scope 4:.:.:A429Decoder.pro:WIN32:
# RC_ICONS = "decode.ico"

#### Keys ignored in scope 5:.:.:A429Decoder.pro:QNX:
# target.path = "/tmp/$${TARGET}/bin"

#### Keys ignored in scope 7:.:.:A429Decoder.pro:UNIX AND NOT ANDROID:
# target.path = "/opt/$${TARGET}/bin"

#### Keys ignored in scope 8:.:.:A429Decoder.pro:NOT target.path_ISEMPTY:
# INSTALLS = "target"

#qt_internal_extend_target(A429Decoder CONDITION WIN32 AND CONFIG(release,debug OR release)
#    PUBLIC_LIBRARIES
#        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../A429Library/build/release/
#        A429Library
#)

#qt_internal_extend_target(A429Decoder CONDITION (NOT (WIN32 AND CONFIG(release,debug OR release))) AND (WIN32 AND CONFIG(debug,debug OR release))
#    PUBLIC_LIBRARIES
#        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../A429Library/build/debug/
#        A429Library
#)

#qt_internal_extend_target(A429Decoder CONDITION ((NOT (WIN32 AND CONFIG(release,debug OR release))) AND (NOT (WIN32 AND CONFIG(debug,debug OR release)))) AND (UNIX)
#    PUBLIC_LIBRARIES
#        # Remove: L${CMAKE_CURRENT_SOURCE_DIR}/../A429Library/build/
#        A429Library
#)

#### Keys ignored in scope 14:.:.:A429Decoder.pro:win32-g++ AND CONFIG(release,debug OR release):
# PRE_TARGETDEPS = "$$PWD/../A429Library/build/release/libA429Library.a"

#### Keys ignored in scope 16:.:.:A429Decoder.pro:win32-g++ AND CONFIG(debug,debug OR release):
# PRE_TARGETDEPS = "$$PWD/../A429Library/build/debug/libA429Library.a"

#### Keys ignored in scope 18:.:.:A429Decoder.pro:WIN32 AND NOT win32-g++ AND CONFIG(release,debug OR release):
# PRE_TARGETDEPS = "$$PWD/../A429Library/build/release/A429Library.lib"

#### Keys ignored in scope 20:.:.:A429Decoder.pro:WIN32 AND NOT win32-g++ AND CONFIG(debug,debug OR release):
# PRE_TARGETDEPS = "$$PWD/../A429Library/build/debug/A429Library.lib"

#### Keys ignored in scope 22:.:.:A429Decoder.pro:UNIX:
# PRE_TARGETDEPS = "$$PWD/../A429Library/build/libA429Library.a"
