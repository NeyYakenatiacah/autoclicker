cmake_minimum_required(VERSION 3.16)

project(win-clicker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)


set(app_executable_name "ABTO607")
set(app_icon_resource_windows "${CMAKE_CURRENT_SOURCE_DIR}/resources/app_icon.rc")

set(PROJECT_SOURCES
        main.cpp
        main_window.cpp
        main_window.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${app_executable_name}
        MANUAL_FINALIZATION
        ${app_icon_resource_windows}
        ${PROJECT_SOURCES}
        controls/capture_widget.h controls/capture_widget.cpp
        system_window_manager.h system_window_manager.cpp
        application_widget.h application_widget.cpp
        system_api.h system_api.cpp
        controls/window_selector.h controls/window_selector.cpp
        controls/process_widget.h controls/process_widget.cpp
        controls/preferences_widget.h controls/preferences_widget.cpp
        controls/auto_clicker.h controls/auto_clicker.cpp
        controls/key_sequence_widget.h controls/key_sequence_widget.cpp
        controls/key_selector_widget.h controls/key_selector_widget.cpp
        controls/hp_clicker.h controls/hp_clicker.cpp
        controls/hp_widget.h controls/hp_widget.cpp
        controls/qpointedit.h controls/qpointedit.cpp
        controls/qcoloredit.h controls/qcoloredit.cpp
        res.qrc
        logger.h logger.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET win-clicker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${app_executable_name} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${app_executable_name}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(${app_executable_name} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.win-clicker)
endif()
set_target_properties(${app_executable_name} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS ${app_executable_name}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${app_executable_name})
endif()
