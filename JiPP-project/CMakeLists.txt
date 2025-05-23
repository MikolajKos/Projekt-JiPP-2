cmake_minimum_required(VERSION 3.20)
project(JiPP_project)

set(CMAKE_CXX_STANDARD 20)

# Biblioteka ze SmartArray i Student
add_library(JiPP_project_smartArray
    src/smartArray/SmartArray.cpp
    src/data/Student.cpp
 )

# Ścieżki do nagłówków
target_include_directories(JiPP_project_smartArray PUBLIC
    ${CMAKE_SOURCE_DIR}/src/smartArray
    ${CMAKE_SOURCE_DIR}/src/data
)

# Plik wykonywalny
add_executable(JiPP_project_app
    src/app/main.cpp
    src/app/Tui.cpp 
    src/app/Tui.h
)

target_include_directories(JiPP_project_app PUBLIC
    ${CMAKE_SOURCE_DIR}/src/smartArray
    ${CMAKE_SOURCE_DIR}/src/data
)

# FTXUI - pobieranie przez FetchContent
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main
)
FetchContent_MakeAvailable(ftxui)

# Linkowanie z FTXUI
target_link_libraries(JiPP_project_app
    JiPP_project_smartArray
    component
    ftxui::screen
    ftxui::dom
    ftxui::component
)

add_subdirectory(tests)