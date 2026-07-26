cmake_minimum_required(VERSION 3.16)
project(Calendar VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if(EXISTS "${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Calendar
    
    main.cpp

    # Model
    src/model/classes/Activity.cpp
    src/model/classes/Task.cpp
    src/model/classes/Event.cpp
    src/model/classes/SimpleTask.cpp
    src/model/classes/Appointment.cpp
    src/model/classes/CompositeTask.cpp
    src/model/ActivityManager/classes/ActivityManager.cpp
    src/model/ActivityManager/headers/ActivityManager.h

    # View
    src/view/classes/MainWindow.cpp
    src/view/classes/DaySelectorWidget.cpp
    src/view/headers/MainWindow.h
)

target_include_directories(Calendar PRIVATE
    ${CMAKE_SOURCE_DIR}/src/model/headers/
    ${CMAKE_SOURCE_DIR}/src/model/ActivityFilters/headers/
    ${CMAKE_SOURCE_DIR}/src/model/ActivityManager/headers/
    ${CMAKE_SOURCE_DIR}/src/view/headers
)
target_link_libraries(Calendar PRIVATE Qt6::Widgets)


set_target_properties(Calendar PROPERTIES
    AUTOMOC ON 
    AUTOUIC ON 
    AUTORCC ON
)

if (WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt)
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Calendar POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:Calendar>)
    endif()
endif()
