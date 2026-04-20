cmake_minimum_required(VERSION 3.16)

# Nome del progetto
project(Calendar VERSION 1.0 LANGUAGES CXX)

# Usa C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64")

# Trova Qt6 Widgets
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Crea l'eseguibile dal main.cpp
add_executable(Calendar
    main.cpp
    src/model/classes/Activity.cpp
    src/model/classes/Task.cpp
    src/model/classes/Event.cpp
    src/model/classes/SimpleTask.cpp
    src/model/classes/Appointment.cpp
    src/model/classes/CompositeTask.cpp
)

# Collega le librerie Qt
target_link_libraries(Calendar PRIVATE Qt6::Widgets)

# Abilita automoc, autouic, autorcc
set_target_properties(Calendar PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Aggiunge le dll per Qt
if (WIN32)
    add_custom_command(TARGET Calendar POST_BUILD
        COMMAND ${CMAKE_SOURCE_DIR}/QT/6.11.0/mingw_64/bin/windeployqt.exe
        $<TARGET_FILE:Calendar>
    )
endif()