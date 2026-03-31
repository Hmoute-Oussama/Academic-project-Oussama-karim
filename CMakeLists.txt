cmake_minimum_required(VERSION 3.16)
project(Academic-project-Oussama-karim)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.10.2/mingw_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Academic-project-Oussama-karim
        main.cpp
        model/Node.cpp
        model/Node.h
        model/Permission.cpp
        model/Permission.h
        model/FileNode.cpp
        model/FileNode.h
        model/DirectoryNode.cpp
        model/DirectoryNode.h
        model/SymLink.cpp
        model/SymLink.h
        model/HardLink.cpp
        model/HardLink.h
        model/FileSystem.cpp
        model/FileSystem.h
        model/PathParser.cpp
        model/PathParser.h
        model/User.cpp
        model/User.h
        model/Group.cpp
        model/Group.h
        model/FileLock.cpp
        model/FileLock.h
        model/Journal.cpp
        model/Journal.h
        model/Snapshot.cpp
        model/Snapshot.h
        model/SearchEngine.cpp
        model/SearchEngine.h
        model/DiskManager.cpp
        model/DiskManager.h
        model/Trash.cpp
        model/Trash.h
        model/Quota.cpp
        model/Quota.h
)

target_link_libraries(Academic-project-Oussama-karim
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()