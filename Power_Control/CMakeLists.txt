cmake_minimum_required(VERSION 3.16)

project(ClassRoom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Sql
    SerialPort
    PrintSupport
)

find_package(Qt5LinguistTools QUIET)

set(PROJECT_SOURCES
    main.cpp
    appinit.cpp
    iconhelper.cpp
    login.cpp
    passwdedit.cpp
    qcustomplot.cpp
    register.cpp
    systemtrayicon.cpp
    mainwindow.cpp
)

set(PROJECT_HEADERS
    appinit.h
    iconhelper.h
    mainwindow.h
    login.h
    passwdedit.h
    qcustomplot.h
    register.h
    systemtrayicon.h
)

set(PROJECT_FORMS
    login.ui
    passwdedit.ui
    register.ui
    mainwindow.ui
)

set(PROJECT_RESOURCES
    myqrc.qrc
    lang.qrc
    qss.qrc
)

set(PROJECT_TRANSLATIONS
    cn.ts
    en.ts
)

add_executable(ClassRoom WIN32
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
    ${PROJECT_FORMS}
    ${PROJECT_RESOURCES}
    myapp.rc
)

target_link_libraries(ClassRoom PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
    Qt5::SerialPort
    Qt5::PrintSupport
)

target_include_directories(ClassRoom PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(ClassRoom PRIVATE
    QT_DEPRECATED_WARNINGS
)

if(Qt5LinguistTools_FOUND)
    qt5_add_translation(QM_FILES ${PROJECT_TRANSLATIONS})
    add_custom_target(update_translations DEPENDS ${QM_FILES})
endif()
