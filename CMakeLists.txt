cmake_minimum_required(VERSION 3.8)
project(flyos_clipboard)

set(CMAKE_CXX_STANDARD 17)

#qt
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(PkgConfig)

pkg_check_modules(DTK REQUIRED
        dtkcore
        dtkwidget
        )

include_directories(${DTK_INCLUDE_DIRS})

set(QRC_FILES
        images/images.qrc
        styles/styles.qrc)

set(SOURCE_FILES
        base/fileUtil.cpp
        base/fileUtil.h

        main.cpp
        mainwindow.cpp
        mainwindow.h

        widgets/ListWidget.cpp
        widgets/ListWidget.h

        widgets/ListItem.cpp
        widgets/ListItem.h widgets/ExitDialog.cpp widgets/ExitDialog.h widgets/AboutDialog.cpp widgets/AboutDialog.h)

add_executable(flyos-clipboard ${SOURCE_FILES} ${QRC_FILES})
target_link_libraries(flyos-clipboard Qt5::Core Qt5::Gui Qt5::Widgets ${DTK_LIBRARIES})

install(TARGETS flyos-clipboard RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES flyos-clipboard.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
install(FILES images/logo.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/64x64/apps RENAME flyos-clipboard.png)
