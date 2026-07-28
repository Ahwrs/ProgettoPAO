cmake_minimum_required(VERSION 3.16)
project(Calendar VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Supporto per un percorso Qt personalizzato (es. per build portabili)
if(EXISTS "${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64")
    list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

set(MODEL_SOURCES
    src/model/classes/Activity.cpp
    src/model/classes/Task.cpp
    src/model/classes/Event.cpp
    src/model/classes/SimpleTask.cpp
    src/model/classes/Appointment.cpp
    src/model/classes/CompositeTask.cpp
    src/model/ActivityManager/classes/ActivityManager.cpp
)

set(MODEL_HEADERS
    src/model/ActivityManager/headers/ActivityManager.h
    
)

set(VIEW_SOURCES
    src/view/classes/MainWindow.cpp
    src/view/classes/DaySelectorWidget.cpp
    src/view/RowWidget/classes/ActivityRow.cpp
    src/view/RowWidget/classes/TaskRow.cpp
    src/view/RowWidget/classes/EventRow.cpp
)

set(VIEW_HEADERS
    src/view/headers/MainWindow.h
    src/view/headers/DaySelectorWidget.h
    src/view/RowWidget/headers/ActivityRow.h
    src/view/RowWidget/headers/TaskRow.h
    src/view/RowWidget/headers/EventRow.h
)


add_executable(Calendar
    main.cpp
    resources/resources.qrc
    ${MODEL_SOURCES}
    ${MODEL_HEADERS}
    ${VIEW_SOURCES}
    ${VIEW_HEADERS}
)


target_include_directories(Calendar PRIVATE
    ${CMAKE_SOURCE_DIR}/src/model/headers/
    ${CMAKE_SOURCE_DIR}/src/model/ActivityFilters/headers/
    ${CMAKE_SOURCE_DIR}/src/model/ActivityManager/headers/
    ${CMAKE_SOURCE_DIR}/src/view/headers
    ${CMAKE_SOURCE_DIR}/src/view/RowWidget/headers
)


target_link_libraries(Calendar PRIVATE Qt6::Widgets Qt6::Svg)

set_target_properties(Calendar PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)


if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt)
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET Calendar POST_BUILD
            COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:Calendar>
            COMMENT "Esecuzione windeployqt per copiare le dipendenze Qt"
        )
    endif()
endif()