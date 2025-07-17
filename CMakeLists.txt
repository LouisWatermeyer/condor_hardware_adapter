cmake_minimum_required(VERSION 3.16)

project(condor_hardware_adapter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Network)
qt_standard_project_setup()

qt_add_executable(condor_hardware_adapter
        main.cpp
        ui/mainwindow.cpp
        ui/mainwindow.h
        ui/mainwindow.ui
        logservice/logservice.h
        logservice/logservice.cpp
        udpservice/UDPService.h
        udpservice/UDPService.cpp)

target_link_libraries(condor_hardware_adapter PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(condor_hardware_adapter PRIVATE Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(condor_hardware_adapter PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS condor_hardware_adapter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
